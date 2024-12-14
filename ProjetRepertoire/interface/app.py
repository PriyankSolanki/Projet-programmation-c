from flask import Flask, render_template, request, redirect, url_for
import os

app = Flask(__name__)

# Chemin du fichier repertoire
#FICHIER_REPERTOIRE = os.path.join(os.path.dirname(__file__), 'data', 'repertoire.txt')
FICHIER_REPERTOIRE = "../cmake-build-debug/repertoire.txt"

def lire_repertoire():
    try:
        if not os.path.exists(FICHIER_REPERTOIRE):
            os.makedirs(os.path.dirname(FICHIER_REPERTOIRE), exist_ok=True)
            open(FICHIER_REPERTOIRE, 'w').close()

        with open(FICHIER_REPERTOIRE, 'r') as f:
            repertoire = []
            for ligne in f:
                champs = ligne.strip().split(';')
                if len(champs) == 4:
                    nom, prenom, tel, mail = champs
                    repertoire.append({'nom': nom, 'prenom': prenom, 'tel': tel, 'mail': mail})
            return repertoire
    except Exception as e:
        print(f"Erreur lors de la lecture du fichier : {e}")
        return []

def sauvegarder_repertoire(repertoire):
    try:
        with open(FICHIER_REPERTOIRE, 'w') as f:
            for contact in repertoire:
                f.write(f"{contact['nom']};{contact['prenom']};{contact['tel']};{contact['mail']}\n")
    except Exception as e:
        print(f"Erreur lors de la sauvegarde du fichier : {e}")

@app.route('/')
def index():
    repertoire = lire_repertoire()
    return render_template('index.html', repertoire=repertoire)

@app.route('/ajouter', methods=['POST'])
def ajouter():
    nom = request.form['nom']
    prenom = request.form['prenom']
    tel = request.form['tel']
    mail = request.form['mail']

    if not nom or not prenom or not tel or not mail:
        return "Tous les champs doivent être remplis.", 400

    repertoire = lire_repertoire()
    repertoire.append({'nom': nom, 'prenom': prenom, 'tel': tel, 'mail': mail})

    sauvegarder_repertoire(repertoire)

    return redirect(url_for('index'))

@app.route('/supprimer', methods=['POST'])
def supprimer():
    nom = request.form['nom']
    prenom = request.form['prenom']

    repertoire = lire_repertoire()

    repertoire = [r for r in repertoire if r['nom'] != nom or r['prenom'] != prenom]

    sauvegarder_repertoire(repertoire)

    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)