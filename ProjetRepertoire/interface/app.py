from flask import Flask, render_template, request, redirect, url_for
import os
import re

app = Flask(__name__)

# Chemin du fichier repertoire
FICHIER_REPERTOIRE = "../cmake-build-debug/repertoire.txt"

# Fonction de validation des noms et prénoms
def est_valide_nom_prenom(nom_prenom):
    regex = r"^[A-Za-zÀ-ÿÉéÈèÊêËëÎîÏïÔôÖöÙùÛûÜüÇç ]+$"
    return bool(re.match(regex, nom_prenom))

# Fonction de validation du numéro de téléphone
def est_valide_tel(tel):
    tel = tel.replace(" ", "")
    return bool(re.match(r"^0\d{9}$", tel))

def lire_repertoire():
    try:
        if not os.path.exists(FICHIER_REPERTOIRE):
            os.makedirs(os.path.dirname(FICHIER_REPERTOIRE), exist_ok=True)
            open(FICHIER_REPERTOIRE, 'wb').close()

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
    return render_template('index.html', repertoire=repertoire, erreur=None)

@app.route('/ajouter', methods=['POST'])
def ajouter():
    nom = request.form['nom']
    prenom = request.form['prenom']
    tel = request.form['tel']
    mail = request.form['mail']

    # Vérifier que tous les champs sont remplis
    if not nom or not prenom or not tel or not mail:
        return render_template('index.html', repertoire=lire_repertoire(), erreur="Tous les champs doivent être remplis.")

    # Valider les noms et prénoms
    if not est_valide_nom_prenom(nom) or not est_valide_nom_prenom(prenom):
        return render_template('index.html', repertoire=lire_repertoire(), erreur="Le nom ou le prénom contient des caractères invalides.")

    # Valider le numéro de téléphone
    if not est_valide_tel(tel):
        return render_template('index.html', repertoire=lire_repertoire(), erreur="Le numéro de téléphone doit commencer par 0 et être sous format 0XXXXXXXXX.")

    repertoire = lire_repertoire()
    repertoire.append({'nom': nom, 'prenom': prenom, 'tel': tel, 'mail': mail})

    sauvegarder_repertoire(repertoire)

    return redirect(url_for('index'))

@app.route('/supprimer_contact/<nom>/<prenom>', methods=['GET'])
def supprimer_contact(nom, prenom):
    repertoire = lire_repertoire()

    # Supprimer le contact en utilisant le nom et prénom
    repertoire = [r for r in repertoire if not (r['nom'] == nom and r['prenom'] == prenom)]

    sauvegarder_repertoire(repertoire)

    return redirect(url_for('index'))


@app.route('/rechercher', methods=['POST'])
def rechercher():
    recherche = request.form['recherche']
    repertoire = lire_repertoire()

    # Filtrer les contacts qui contiennent la recherche dans le nom ou le prénom
    repertoire_filtré = [r for r in repertoire if recherche.lower() in r['nom'].lower() or recherche.lower() in r['prenom'].lower()]

    return render_template('index.html', repertoire=repertoire_filtré, erreur=None)

if __name__ == '__main__':
    app.run(debug=True)
