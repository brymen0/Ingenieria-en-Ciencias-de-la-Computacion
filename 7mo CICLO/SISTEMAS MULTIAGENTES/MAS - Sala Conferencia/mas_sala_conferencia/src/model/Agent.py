class Agent:
    def __init__(self, name, message_bus):
        self.name = name
        self.bus = message_bus
        self.bus.subscribe(name, self.receive_message)

    def send_message(self, to_agent, message):
        self.bus.send_message(to_agent, message)

    def receive_message(self, message):
        print(f"[{self.name}] recibió mensaje: {message}")
