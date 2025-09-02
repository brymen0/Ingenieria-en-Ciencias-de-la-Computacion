import pygame

class SpriteVentanilla(pygame.sprite.Sprite):
    def __init__(self, ventanilla, coordenadas_atencion, coordenadas, *groups):
        super().__init__(*groups)
        self.ventanilla = ventanilla  # referencia al modelo
        self.image = pygame.transform.scale(pygame.image.load("resources/ventanilla.jpg"),(120, 115))
        self.rect = coordenadas
        self.coordenadas_atencion = coordenadas_atencion
  