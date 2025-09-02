import threading
import json
import pika
import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext
from agents.autenticacion import AgenteAutenticacion
from agents.usuarios import AgenteUsuarios

#g_host = "186.43.217.213"
#g_host = "186.43.199.8"
g_host = "10.26.16.99"
g_user = "user"
g_pass = "user"
ACL_EXCHANGE = "fipa_acl"

class EmailClientApp:
    def __init__(self):
        self.auth_agent = AgenteAutenticacion(api_url=f"http://{g_host}:5000")
        self.user_agent = AgenteUsuarios(api_url=f"http://{g_host}:5000")
        self.user = None

        self.root = tk.Tk()
        self.root.title("Correo Multiagente – Login")
        self.root.configure(bg="#f0f0f0")
        self.root.state("zoomed")
        self.build_login_ui()
        self.root.mainloop()

    def build_login_ui(self):
        main_frame = tk.Frame(self.root, bg="#ffffff", bd=2, relief="solid")
        main_frame.place(relx=0.5, rely=0.5, anchor="center")

        entry_style = {"font": ("Segoe UI", 11), "relief": "solid", "bd": 1, "bg": "#f9f9f9"}

        main_frame.columnconfigure(0, weight=1)
        main_frame.columnconfigure(1, weight=2)

        tk.Label(main_frame, text="CorreoMAS.com", font=("Segoe UI", 18, "bold"), bg="#ffffff")\
            .grid(row=0, column=0, columnspan=2, pady=(20, 10))

        tk.Label(main_frame, text="Correo:", font=("Segoe UI", 11), bg="#ffffff")\
            .grid(row=1, column=0, sticky="e", padx=10, pady=10)
        self.e_user = tk.Entry(main_frame, width=30, **entry_style)
        self.e_user.grid(row=1, column=1, sticky="w", padx=10, pady=10)

        tk.Label(main_frame, text="Contraseña:", font=("Segoe UI", 11), bg="#ffffff")\
            .grid(row=2, column=0, sticky="e", padx=10, pady=10)
        self.e_pass = tk.Entry(main_frame, show="*", width=30, **entry_style)
        self.e_pass.grid(row=2, column=1, sticky="w", padx=10, pady=10)

        login_button = tk.Button(
            main_frame, text="Iniciar sesión", command=self.do_login,
            font=("Segoe UI", 11, "bold"), bg="#000000", fg="#ffffff",
            activebackground="#333333", activeforeground="#ffffff",
            relief="flat", width=20
        )
        login_button.grid(row=3, column=0, columnspan=2, pady=20, padx=10, sticky="ew")

    def do_login(self):
        correo = self.e_user.get().strip()
        clave = self.e_pass.get().strip()
    
        if not self.auth_agent.autenticar(correo, clave):
            messagebox.showerror("Error", "Credenciales inválidas")
            return
        self.user = correo
        self.root.destroy()
        self.build_main_ui()
        self.start_rabbit_consumer()
        self.win.mainloop()

    def build_main_ui(self):
        self.win = tk.Tk()
        self.win.title("Correo de " + self.user)
        self.win.state("zoomed")
        self.win.configure(bg="#f0f0f0")

        main_frame = tk.Frame(self.win, bg="#ffffff", bd=2, relief="groove", padx=30, pady=30)
        main_frame.place(relx=0.5, rely=0.5, anchor="center")

        tk.Label(main_frame, text="Enviar Correo", font=("Segoe UI", 20, "bold"),
                 bg="#ffffff", fg="#333333").grid(row=0, column=0, columnspan=2, pady=(10, 20))

        entry_style = {"font": ("Segoe UI", 11), "relief": "solid", "bd": 1, "bg": "#f9f9f9"}

        tk.Label(main_frame, text="Para:", font=("Segoe UI", 11), bg="#ffffff")\
            .grid(row=1, column=0, sticky="e", padx=10, pady=10)
        self.dest_var = tk.StringVar()
        self.to_entry = tk.Entry(main_frame, width=40, textvariable=self.dest_var, **entry_style)
        self.to_entry.grid(row=1, column=1, sticky="w", padx=10, pady=10)

        tk.Label(main_frame, text="Asunto:", font=("Segoe UI", 11), bg="#ffffff")\
            .grid(row=2, column=0, sticky="e", padx=10, pady=10)
        self.e_subject = tk.Entry(main_frame, width=40, **entry_style)
        self.e_subject.grid(row=2, column=1, sticky="w", padx=10, pady=10)

        tk.Label(main_frame, text="Mensaje:", font=("Segoe UI", 11), bg="#ffffff")\
            .grid(row=3, column=0, sticky="ne", padx=10, pady=10)
        self.txt_body = tk.Text(main_frame, width=50, height=10, font=("Segoe UI", 11),
                                relief="solid", bd=1, bg="#f9f9f9")
        self.txt_body.grid(row=3, column=1, sticky="w", padx=10, pady=10)

        send_button = tk.Button(main_frame, text="Enviar", command=self.send_email, width=20)
        send_button.grid(row=4, column=0, columnspan=2, pady=(20, 10))

        send_button.configure(
            bg="#000000", fg="white", activebackground="#333333", activeforeground="white",
            relief="flat", font=("Segoe UI", 11), bd=0, cursor="hand2"
        )

        ttk.Label(main_frame, text="Bandeja de entrada:", font=("Segoe UI", 14, "bold"), background="#ffffff")\
            .grid(row=5, column=0, sticky="nw", padx=10, pady=(20, 5))

        self.txt_inbox = scrolledtext.ScrolledText(
            main_frame, width=50, height=10, font=("Segoe UI", 11), state="disabled",
            relief="solid", bd=1, bg="#f9f9f9"
        )
        self.txt_inbox.grid(row=5, column=1, sticky="w", padx=10, pady=(20, 5))

        main_frame.columnconfigure(1, weight=1)

    def send_email(self):
        acl_msg = {
            "performative": "request",
            "sender": self.user,
            "receiver": "AgenteEnvio",
            "ontology": "email",
            "content": {
                "action": "send_email",
                "from": self.user,
                "to": self.dest_var.get(),
                "subject": self.e_subject.get().strip(),
                "body": self.txt_body.get("1.0", "end").strip()
            }
        }
        try:
            creds = pika.PlainCredentials(g_user, g_pass)
            params = pika.ConnectionParameters(host=g_host, port=5672, credentials=creds)
            ch = pika.BlockingConnection(params).channel()
            ch.exchange_declare(exchange=ACL_EXCHANGE, exchange_type="topic", durable=True)
            ch.basic_publish(
                exchange=ACL_EXCHANGE,
                routing_key="AgenteEnvio",
                body=json.dumps(acl_msg),
                properties=pika.BasicProperties(delivery_mode=2)
            )
            ch.close()
            messagebox.showinfo("Enviado", "Solicitud de envío enviada.")
            self.e_subject.delete(0, "end")
            self.txt_body.delete("1.0", "end")
        except Exception as e:
            messagebox.showerror("Error al enviar", str(e))

    def start_rabbit_consumer(self):
        creds = pika.PlainCredentials(g_user, g_pass)
        params = pika.ConnectionParameters(host=g_host, port=5672, credentials=creds)
        conn = pika.BlockingConnection(params)
        ch = conn.channel()
        ch.exchange_declare(exchange=ACL_EXCHANGE, exchange_type="topic", durable=True)

        acl_queue = f"{self.user}_acl"
        ch.queue_declare(queue=acl_queue, durable=True)
        ch.queue_bind(queue=acl_queue, exchange=ACL_EXCHANGE, routing_key=self.user)

        def on_message(ch, method, props, body):
            msg = json.loads(body)
            if msg.get("performative") == "inform":
                c = msg.get("content", {})
                texto = (
                    f"De: {c.get('from')}\n"
                    f"Asunto: {c.get('subject')}\n\n"
                    f"{c.get('body')}\n" + "-" * 40 + "\n"
                )
                self.txt_inbox.configure(state="normal")
                self.txt_inbox.insert("end", texto)
                self.txt_inbox.configure(state="disabled")
                messagebox.showinfo("Nuevo correo", f"{c.get('subject')} de {c.get('from')}")

        ch.basic_consume(queue=acl_queue, on_message_callback=on_message, auto_ack=True)
        threading.Thread(target=ch.start_consuming, daemon=True).start()


if __name__ == "__main__":
    EmailClientApp()
