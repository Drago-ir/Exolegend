# Exolegend

## Installation

### [Option A] Création d'un repository dédié via un fork sur GitLab

- Connectez vous à [https://gitlab.com](https://gitlab.com) à l'aide de votre compte personnel. 
- Rendez vous sur la page : [https://gitlab.com/exolegend/exolegend](https://gitlab.com/exolegend/exolegend).
- Cliquez sur le bouton "fork" afin de créer forker le projet dans un repository privée. ![How to fork 1](./images/readme_fork_1.jpg)
- Paramétre votre fork avec un nom, le dossier dans lequel le ranger, n'oubliez pas de mettre votre repository en privée pour ne pas divulguer votre code ! Confirmez ensuite le fork. ![How to fork 2](./images/readme_fork_2.jpg)
- Un nouveau repository privée se trouvera a présent dans votre liste de repository. Clonez ensuite ce repository en local sur votre machine. ![How to fork 3](./images/readme_fork_3.jpg)
```
$ git clone git@gitlab.com:User/exolegend-oh-my-strategy.git
  Cloning into 'exolegend-oh-my-strategy'...
  Enter passphrase for key '/home/user/.ssh/private_id_rsa':
  remote: Enumerating objects: 3, done.
  remote: Counting objects: 100% (3/3), done.
  remote: Compressing objects: 100% (2/2), done.
  remote: Total 3 (delta 0), reused 3 (delta 0), pack-reused 0
  Receiving objects: 100% (3/3), done.
```
- Ajoutez le lien : "upstream" du repository d'exolegend pour les mises à jour.
```
$ cd exolegend-oh-my-strategy
$ git remote add upstream git@gitlab.com:exolegend/exolegend.git
```

### [Option B] Cloner sans création de repository dédié

- Connectez vous à [https://gitlab.com](https://gitlab.com) à l'aide de votre compte personnel.
- Rendez vous sur la page : [https://gitlab.com/exolegend/exolegend](https://gitlab.com/exolegend/exolegend).
- Clonez ce repository en local sur votre machine. ![How to clone 1](./images/readme_clone_1.jpg)
```
$ git clone git@gitlab.com:exolegend/exolegend.git
  Cloning into 'exolegend-oh-my-strategy'...
  Enter passphrase for key '/home/user/.ssh/private_id_rsa':
  remote: Enumerating objects: 3, done.
  remote: Counting objects: 100% (3/3), done.
  remote: Compressing objects: 100% (2/2), done.
  remote: Total 3 (delta 0), reused 3 (delta 0), pack-reused 0
  Receiving objects: 100% (3/3), done.
```
- Ajoutez le lien : "upstream" du repository d'Exolegend pour les mises à jour.
```
$ cd exolegend-oh-my-strategy
$ git remote add upstream git@gitlab.com:exolegend/exolegend.git
```

## Mise à jour

- Pour récupérer les mises à jour entrez la commande : `$ git fetch upstream`.
- Pour mettre à jour votre branche de travail, mergez le tag : `RELEASE_X` : `$ git merge RELEASE_X`. (La disponibilité des tags seront communiqué lors de leur sortie)

## Dépendances

TO DO

## Par où commencer ?

TO DO
