from flask import Flask, jsonify, render_template
import ctypes
import os

app = Flask(__name__)

_lib_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "libfila.so")
lib = ctypes.CDLL(_lib_path)

class Carrinho(ctypes.Structure):
	_fields_ = [
		("banana", ctypes.c_int),
		("feijao", ctypes.c_int),
		("leite", ctypes.c_int),
		("arroz", ctypes.c_int),
		("valor", ctypes.c_int),
	]

class Cliente(ctypes.Structure):
	_fields_ = [
		("id", ctypes.c_int),
		("nota", ctypes.c_int * 5),
		("carrinho", Carrinho),
	]

class Elemento(ctypes.Structure):
	pass

ElementoPtr = ctypes.POINTER(Elemento)
Elemento._fields_ = [
	("cliente", Cliente),
	("prox", ElementoPtr),
]

class Fila(ctypes.Structure):
	_fields_ = [
		("inicio", ElementoPtr),
		("fim", ElementoPtr),
	]

FilaPtr = ctypes.POINTER(Fila)
ClientePtr = ctypes.POINTER(Cliente)

lib.somar_carrinho.restype = None
lib.somar_carrinho.argtypes = [ClientePtr]

lib.gerar_dinheiro.restype = None
lib.gerar_dinheiro.argtypes = [ClientePtr]

lib.pagar_conta.restype = ctypes.c_int
lib.pagar_conta.argtypes = [ClientePtr]

lib.criar_fila.restype = FilaPtr
lib.criar_fila.argtypes = []

lib.inserir_na_fila.restype = ctypes.c_int
lib.inserir_na_fila.argtypes = [FilaPtr, Cliente]

lib.atender.restype = ElementoPtr
lib.atender.argtypes = [FilaPtr]

lib.liberar_elemento.restype = None
lib.liberar_elemento.argtypes = [ElementoPtr]

lib.liberar_fila.restype = None
lib.liberar_fila.argtypes = [FilaPtr]

lib.simular_atendimento.restype = ctypes.c_int
lib.simular_atendimento.argtypes = [FilaPtr]

lib.simular_dia.restype = None
lib.simular_dia.argtypes = [FilaPtr]


def _simular_dia():
	fila = lib.criar_fila()
	if not fila:
		raise MemoryError("Não foi possível criar a fila de atendimento.")

	try:
		for indice in range(10):
			cliente = Cliente()
			cliente.id = indice + 1
			cliente.carrinho.arroz = indice + 1
			cliente.carrinho.banana = indice + 4
			cliente.carrinho.feijao = indice + 1
			cliente.carrinho.leite = indice + 3

			if not lib.inserir_na_fila(fila, cliente):
				raise MemoryError("Não foi possível adicionar um cliente à fila.")

		clientes = []
		while True:
			elemento = lib.atender(fila)
			if not elemento:
				break

			try:
				cliente = elemento.contents.cliente
				cliente_ptr = ctypes.byref(cliente)
				lib.somar_carrinho(cliente_ptr)
				lib.gerar_dinheiro(cliente_ptr)
				pagamento_aprovado = bool(lib.pagar_conta(cliente_ptr))
				dinheiro = sum(cliente.nota)

				clientes.append({
					"id": cliente.id,
					"carrinho": {
						"banana": cliente.carrinho.banana,
						"feijao": cliente.carrinho.feijao,
						"leite": cliente.carrinho.leite,
						"arroz": cliente.carrinho.arroz,
					},
					"total": cliente.carrinho.valor,
					"dinheiro": dinheiro,
					"pagamento_aprovado": pagamento_aprovado,
				})
			finally:
				lib.liberar_elemento(elemento)

		return clientes
	finally:
		lib.liberar_fila(fila)


@app.get("/")
def index():
	return render_template("index.html")


@app.post("/api/simular")
def api_simular():
	try:
		clientes = _simular_dia()
	except MemoryError as erro:
		return jsonify({"erro": str(erro)}), 503
	except Exception:
		app.logger.exception("Falha ao executar a simulação")
		return jsonify({"erro": "Não foi possível concluir a simulação."}), 500

	aprovados = [cliente for cliente in clientes if cliente["pagamento_aprovado"]]
	return jsonify({
		"clientes": clientes,
		"resumo": {
			"atendidos": len(clientes),
			"aprovados": len(aprovados),
			"recusados": len(clientes) - len(aprovados),
			"total_vendido": sum(cliente["total"] for cliente in aprovados),
		},
	})


if __name__ == "__main__":
	app.run(host="127.0.0.1", port=5000, debug=True)


