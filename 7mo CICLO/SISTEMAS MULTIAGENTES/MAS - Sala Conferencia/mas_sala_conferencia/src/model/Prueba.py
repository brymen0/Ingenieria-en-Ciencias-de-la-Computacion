from MessageBus import MessageBus
from AgenteAcceso import AgenteAcceso
from AgenteOcupacion import AgenteOcupacion
from AgenteControlTemperatura import AgenteControlTemperatura
from AgenteControlEnergia import AgenteControlEnergia
from AgentePonencia import AgentePonencia
from AgenteReservas import AgenteReservas

bus = MessageBus()

acceso = AgenteAcceso("AgenteAcceso", bus)
ocupacion = AgenteOcupacion("AgenteOcupacion", bus)
temperatura = AgenteControlTemperatura("AgenteControlTemperatura", bus)
energia = AgenteControlEnergia("AgenteControlEnergia", bus)
ponencia = AgentePonencia("AgentePonencia", bus)
reservas = AgenteReservas("AgenteReservas", bus)

ocupacion.contar_personas(48)

ponencia.iniciar_ponencia("Dra. Pérez")

reservas.nueva_reserva("Juan", "10:00 AM")
