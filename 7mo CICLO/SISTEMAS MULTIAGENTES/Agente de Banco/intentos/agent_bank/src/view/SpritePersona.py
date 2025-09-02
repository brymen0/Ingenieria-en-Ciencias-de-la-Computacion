import pygame
import time
from model.constantes import ESTADOS_FILA

class SpritePersona(pygame.sprite.Sprite):
    def __init__(self, persona, text_imagen, *groups):
        super().__init__(*groups)
        self.persona = persona  # referencia al modelo
        self.image = pygame.image.load(f"resources/{text_imagen}.png")
        self.index = 0
        self.x, self.y = ESTADOS_FILA[0]
        self.rect = self.image.get_rect(topleft=(self.x, self.y))
        self.destino = self.x, self.y
        self.moviendo = False
        self.velocidad = 2
    
    def mover(self, x, y):
        self.destino = (x, y)
        self.moviendo = True

    def actualizar(self):
        self.moviendo = False  # Detener cualquier otro movimiento automático
        while abs(self.x - self.destino[0]) > 2 or abs(self.y - self.destino[1]) > 2:
            if self.x < self.destino[0]:
                self.x += 2
            elif self.x > self.destino[0]:
                self.x -= 2

            if self.y < self.destino[1]:
                self.y += 2
            elif self.y > self.destino[1]:
                self.y -= 2

            self.rect.topleft = (round(self.x), round(self.y))

            pygame.display.update()  # Para forzar que se vea el movimiento
            time.sleep(0.01)  # Pausa para que se note el avance

        # Asegura que quede exactamente en la posición destino
        self.x, self.y =self.destino
        self.rect.topleft = self.destino

    def actualizar2(self):
        if self.moviendo:
            if abs(self.x - self.destino[0]) > 2:
                self.x += 2 if self.x < self.destino[0] else -2
            else:
                self.x = self.destino[0]

            if abs(self.y - self.destino[1]) > 2:
                self.y += 2 if self.y < self.destino[1] else -2
            else:
                self.y = self.destino[1]

            self.rect.topleft = (round(self.x), round(self.y))

            if self.x == self.destino[0] and self.y == self.destino[1]:
                self.moviendo = False

    def actualizar1(self):
        if self.moviendo:
            dx = self.destino[0] - self.x
            dy = self.destino[1] - self.y
            distancia = (dx**2 + dy**2)**0.5

            if distancia > self.velocidad:
                self.x += self.velocidad * (dx / distancia)
                self.y += self.velocidad * (dy / distancia)
                self.rect.topleft = (round(self.x), round(self.y))
            else:
                self.x, self.y = self.destino
                self.rect.topleft = (self.x, self.y)
                self.moviendo = False
