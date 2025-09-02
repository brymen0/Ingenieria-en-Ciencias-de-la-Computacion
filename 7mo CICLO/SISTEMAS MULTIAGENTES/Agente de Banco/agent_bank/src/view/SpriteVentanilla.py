import pygame

class SpriteVentanilla(pygame.sprite.Sprite):
    def __init__(self, ventanilla, coordenadas, *groups):
        super().__init__(*groups)
        self.ventanilla = ventanilla  # referencia al modelo
        self.image = pygame.transform.scale(pygame.image.load("resources/ventanilla.jpg"),(120, 115))
        self.rect = coordenadas
  