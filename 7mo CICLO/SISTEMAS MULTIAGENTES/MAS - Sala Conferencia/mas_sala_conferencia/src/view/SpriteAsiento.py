import pygame

class SpriteAsiento(pygame.sprite.Sprite):
    def __init__(self, asiento, coordenadas, *groups):
        super().__init__(*groups)
        self.asiento = asiento  # referencia al modelo
        self.image = pygame.image.load("resources/sofa.png")
        self.rect = coordenadas