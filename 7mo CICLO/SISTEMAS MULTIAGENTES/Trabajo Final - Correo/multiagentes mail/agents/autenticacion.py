import requests

class AgenteAutenticacion:
    def __init__(self, api_url="http://186.43.217.213:5000"):
        self.api_url = api_url.rstrip("/")

    def autenticar(self, correo: str, password: str) -> bool:
        try:
            resp = requests.post(
                f"{self.api_url}/login",
                json={"correo": correo, "password": password},
                timeout=5
            )
            return resp.status_code == 200 and resp.json().get("success", False)
        except requests.RequestException:
            return False
