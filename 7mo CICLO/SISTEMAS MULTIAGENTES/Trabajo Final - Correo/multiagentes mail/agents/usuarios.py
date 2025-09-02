import requests

class AgenteUsuarios:
    def __init__(self, api_url="http://186.43.217.213:5000"):
        self.api_url = api_url.rstrip("/")

    def listar(self) -> list:
        try:
            resp = requests.get(f"{self.api_url}/users", timeout=5)
            if resp.status_code == 200:
                return resp.json().get("users", [])
        except requests.RequestException:
            pass
        return []
