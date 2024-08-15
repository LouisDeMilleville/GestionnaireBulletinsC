--
-- Création de la base de données :
--

DROP DATABASE IF EXISTS ProjetInfo;

CREATE DATABASE ProjetInfo CHARACTER SET 'utf8';

USE ProjetInfo;

--
-- Création des tables :
--

CREATE TABLE Eleve (
	ele_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	ele_nom VARCHAR(50) NOT NULL,
	ele_prenom VARCHAR(50) NOT NULL,
	ele_identifiant VARCHAR (50) NOT NULL,
	ele_motdepasse VARCHAR (50) NOT NULL,
	PRIMARY KEY (ele_id)
)
ENGINE=INNODB;

CREATE TABLE Enseignant (
	ens_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	ens_nom VARCHAR(50) NOT NULL,
	ens_prenom VARCHAR(50) NOT NULL,
	ens_identifiant VARCHAR (50) NOT NULL,
	ens_motdepasse VARCHAR (50) NOT NULL,
	ens_matiere VARCHAR (50) NOT NULL,
	PRIMARY KEY (ens_id)
)
ENGINE=INNODB;

CREATE TABLE Secretariat (
	sec_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	sec_nom VARCHAR(50) NOT NULL,
	sec_prenom VARCHAR(50) NOT NULL,
	sec_identifiant VARCHAR (50) NOT NULL,
	sec_motdepasse VARCHAR (50) NOT NULL,
	PRIMARY KEY (sec_id)
)
ENGINE=INNODB;

CREATE TABLE Bulletin (
	bul_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	bul_nom VARCHAR(50) NOT NULL,
	bul_prenom VARCHAR(50) NOT NULL,
	bul_annee INT,
	PRIMARY KEY (bul_id)
)
ENGINE=INNODB;

CREATE TABLE Appreciation (
    app_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
    app_nom_eleve VARCHAR(50) NOT NULL,
    app_prenom_eleve VARCHAR(50) NOT NULL,
    app_nom_enseignant VARCHAR(50) NOT NULL,
    app_prenom_enseignant VARCHAR(50) NOT NULL,
    app_matiere VARCHAR(50) NOT NULL,
    app_texte VARCHAR(300) NOT NULL,
    app_annee INT UNSIGNED NOT NULL,
    app_etat_validation INT UNSIGNED NOT NULL,
    PRIMARY KEY (app_id)
)
ENGINE=INNODB;

CREATE TABLE Est_dans_groupe (
    est_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	est_eleve INT UNSIGNED NOT NULL,
	est_groupe INT UNSIGNED NOT NULL,
	PRIMARY KEY (est_id)
)
ENGINE=INNODB;

CREATE TABLE ens_dans (
    ens_dans_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	ens_dans_ens INT UNSIGNED NOT NULL,
	ens_dans_grp INT UNSIGNED NOT NULL,
	PRIMARY KEY (ens_dans_id)
)
ENGINE=INNODB;




--
-- Insertion de valeurs
--

INSERT INTO Secretariat
VALUES (1, 'Secretariat', 'Compte', 'admin', 'pass');

