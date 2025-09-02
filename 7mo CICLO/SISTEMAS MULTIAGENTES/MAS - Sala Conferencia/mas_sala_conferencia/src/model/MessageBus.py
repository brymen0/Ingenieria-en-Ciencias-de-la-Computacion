class MessageBus:
    def __init__(self):
        self.subscribers = {}

    def subscribe(self, agent_name, callback):
        self.subscribers[agent_name] = callback

    def send_message(self, to_agent, message):
        if to_agent in self.subscribers:
            self.subscribers[to_agent](message)

    def broadcast(self, message):
        for callback in self.subscribers.values():
            callback(message)
