PYTHON = python3
REQUIREMENTS = requirements.txt
APP = app.py

.PHONY: default
default:
	@echo "Installation des dépendances..."
	$(PYTHON) -m pip3 install -r $(REQUIREMENTS)
	@echo "Lancement de l'application..."
	$(PYTHON) $(APP)
