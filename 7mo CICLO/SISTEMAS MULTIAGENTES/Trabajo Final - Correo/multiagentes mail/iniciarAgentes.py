import time
from agents.envio         import AgenteEnvio
from agents.criptografico import AgenteCriptografico
from agents.enrutamiento  import AgenteEnrutamiento
from agents.amenazas      import AgenteDeteccionAmenazas
from agents.recepcion     import AgenteRecepcion
from agents.notificacion  import AgenteNotificacion

if __name__ == "__main__":
    AgenteEnvio()
    AgenteCriptografico()
    AgenteEnrutamiento()
    AgenteDeteccionAmenazas()
    AgenteRecepcion()
    AgenteNotificacion()
    while True:
        time.sleep(1)