#include <stdlib.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

struct Compte
{
       char identifiant[50];
       char mot_de_passe[50];
       char nom [50];
       char prenom[50];
       char matiere[50];

};

struct Compte viderCompte(struct Compte compteAVider)
{
    char chaineVide[50] = "                                                  ";
    strcpy(compteAVider.nom, chaineVide);
    strcpy(compteAVider.prenom, chaineVide);
    strcpy(compteAVider.identifiant, chaineVide);
    strcpy(compteAVider.mot_de_passe, chaineVide);
    strcpy(compteAVider.matiere, chaineVide);

    return compteAVider;
}

void interfaceEleve(struct Compte compteEleve)
{
    int quitter = 0, choix;
    printf("Bonjour %s %s, vous êtes connecté sur l'interface élève\n\n", compteEleve.prenom, compteEleve.nom);
    do
    {
        printf("****************************************\n");
        printf("*                                      *\n");
        printf("*            INTERFACE ELEVE           *\n");
        printf("*                                      *\n");
        printf("****************************************\n");
        printf("1 - Consulter vos bulletins\n");
        printf("2 - Quitter\n");
        printf("Faites votre choix\n");
        scanf("%d", &choix);
        switch(choix)
        {
            case 1:
                system("clear");
                afficherBulletin(compteEleve.nom, compteEleve.prenom);
                break;
            case 2:
                system("clear");
                printf("Déconnexion en cours...\n");
                quitter = 1;
                break;
            default:
                system("clear");
                printf("Erreur d'exécution\n");

        }
    }while(quitter == 0);
}

void interfaceEnseignant(struct Compte compteEnseignant)
{
    int quitter = 0, choix;
    char nom[50], prenom[50];
    printf("Bonjour %s %s, vous êtes connecté sur l'interface enseignant\n\n", compteEnseignant.prenom, compteEnseignant.nom);
    do
    {
        printf("****************************************\n");
        printf("*                                      *\n");
        printf("*         INTERFACE ENSEIGNANT         *\n");
        printf("*                                      *\n");
        printf("****************************************\n");
        printf("1 - Saisir des appréciations\n");
        printf("2 - Consulter les bulletins d'un élève\n");
        printf("3 - Modifier des appréciations en attente de validation\n");
        printf("4 - Consulter les appréciations des autres enseignants\n");
        printf("5 - Quitter\n");
        printf("Faites votre choix\n");
        scanf("%d", &choix);
        switch(choix)
        {
            case 1:
                system("clear");
                ajouterAppreciation(compteEnseignant);
                break;
            case 2:
                system("clear");
                printf("Saisissez le nom de l'élève :\n");
                __fpurge(stdin);
                fgets(nom, 50, stdin);
                nom[strcspn(nom, "\n")] = 0;
                printf("Saisissez le prénom de l'élève :\n");
                __fpurge(stdin);
                fgets(prenom, 50, stdin);
                prenom[strcspn(prenom, "\n")] = 0;
                afficherBulletin(nom, prenom);
                break;
            case 3:
                system("clear");
                modifierAppreciation(compteEnseignant);
                break;
            case 4:
                system("clear");
                voirAppreciation();
                break;
            case 5:
                system("clear");
                printf("Déconnexion en cours...\n");
                quitter = 1;
                break;
            default:
                system("clear");
                printf("Erreur d'exécution\n");

        }
    }while(quitter == 0);
}

void interfaceSecretariat(struct Compte compteSecretariat)
{
    int quitter = 0, choix;
    printf("Bonjour %s %s, vous êtes connecté sur l'interface secrétariat\n\n", compteSecretariat.prenom, compteSecretariat.nom);
    do
    {
        printf("****************************************\n");
        printf("*                                      *\n");
        printf("*        INTERFACE SECRETARIAT         *\n");
        printf("*                                      *\n");
        printf("****************************************\n");
        printf("1 - Créer un nouveau compte\n");
        printf("2 - Ajouter un élève ou un enseignant à un groupe\n");
        printf("3 - Valider des appréciations en attente\n");
        printf("4 - Créer des bulletins\n");
        printf("5 - Quitter\n");
        printf("Faites votre choix\n");
        scanf("%d", &choix);
        switch(choix)
        {
            case 1:
                system("clear");
                creerCompte();
                break;
            case 2:
                system("clear");
                ajouterDansGroupe();
                break;
            case 3:
                system("clear");
                validerAppreciation();
                break;
            case 4:
                system("clear");
                creerBulletin();

                break;
            case 5:
                system("clear");
                printf("Déconnexion en cours...\n");
                quitter = 1;
                break;
            default:
                system("clear");
                printf("Erreur d'exécution\n");

        }
    }while(quitter == 0);
}

void creerCompte()
{

    //INITIALISATION DE LA BDD
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
    }

    if (mysql_real_connect(con, "localhost", "esigelec", "esigelec", "ProjetInfo", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Probleme de connexion\n");
    }

    MYSQL_RES *result;
    //FIN INITIALISATION BDD
    int quitter = 0, choix;
    char nom[50];
    char prenom[50];
    char identifiant[50];
    char mot_de_passe[50];
    char matiere[50];
    char requete[300];

    do
    {
        printf("****************************************\n");
        printf("*                                      *\n");
        printf("*         CREATION DE COMPTE           *\n");
        printf("*                                      *\n");
        printf("****************************************\n");
        printf("1 - Créer un compte secrétariat\n");
        printf("2 - Créer un compte enseignant\n");
        printf("3 - Créer un compte élève\n");
        printf("4 - Quitter\n");
        printf("Faites votre choix\n");
        scanf("%d", &choix);
        switch(choix)
        {
            case 1:
                printf("Saisissez le nom du compte secrétariat à ajouter :\n");
                __fpurge(stdin);
                fgets(nom, 50, stdin);
                nom[strcspn(nom, "\n")] = 0;
                printf("Saisissez le prenom du compte secrétariat à ajouter :\n");
                __fpurge(stdin);
                fgets(prenom, 50, stdin);
                prenom[strcspn(prenom, "\n")] = 0;
                printf("Saisissez l'identifiant du compte secrétariat à ajouter :\n");
                __fpurge(stdin);
                fgets(identifiant, 50, stdin);
                identifiant[strcspn(identifiant, "\n")] = 0;
                printf("Saisissez le mot de passe du compte secrétariat à ajouter :\n");
                __fpurge(stdin);
                fgets(mot_de_passe, 50, stdin);
                mot_de_passe[strcspn(mot_de_passe, "\n")] = 0;
                sprintf(requete, "INSERT INTO Secretariat (sec_nom, sec_prenom, sec_identifiant, sec_motdepasse) VALUES ('%s', '%s', '%s', '%s')", nom, prenom, identifiant, mot_de_passe);
                if (mysql_query(con, requete))
                {
                    printf("Erreur\n");
                }
                result = mysql_store_result(con);
                system("clear");
                printf("Compte secrétariat ajouté !\n");
                mysql_free_result(result);
                break;
                //FIN AJOUT COMPTE SECRETARIAT


            case 2:
                printf("Saisissez le nom du compte enseignant à ajouter :\n");
                __fpurge(stdin);
                fgets(nom, 50, stdin);
                nom[strcspn(nom, "\n")] = 0;
                printf("Saisissez le prenom du compte enseignant à ajouter :\n");
                __fpurge(stdin);
                fgets(prenom, 50, stdin);
                prenom[strcspn(prenom, "\n")] = 0;
                printf("Saisissez l'identifiant du compte enseignant à ajouter :\n");
                __fpurge(stdin);
                fgets(identifiant, 50, stdin);
                identifiant[strcspn(identifiant, "\n")] = 0;
                printf("Saisissez le mot de passe du compte enseignant à ajouter :\n");
                __fpurge(stdin);
                fgets(mot_de_passe, 50, stdin);
                mot_de_passe[strcspn(mot_de_passe, "\n")] = 0;
                printf("Saisissez la matière du compte enseignant à ajouter :\n");
                __fpurge(stdin);
                fgets(matiere, 50, stdin);
                matiere[strcspn(matiere, "\n")] = 0;
                sprintf(requete, "INSERT INTO Enseignant (ens_nom, ens_prenom, ens_identifiant, ens_motdepasse, ens_matiere) VALUES ('%s', '%s', '%s', '%s', '%s')", nom, prenom, identifiant, mot_de_passe, matiere);
                if (mysql_query(con, requete))
                {
                    printf("Erreur !\n");
                }
                result = mysql_store_result(con);
                system("clear");
                printf("Compte enseignant ajouté !\n");
                mysql_free_result(result);
                break;
                //FIN AJOUT COMPTE ENSEIGNANT


            case 3:
                printf("Saisissez le nom du compte élève à ajouter :\n");
                __fpurge(stdin);
                fgets(nom, 50, stdin);
                nom[strcspn(nom, "\n")] = 0;
                printf("Saisissez le prenom du compte élève à ajouter :\n");
                __fpurge(stdin);
                fgets(prenom, 50, stdin);
                prenom[strcspn(prenom, "\n")] = 0;
                printf("Saisissez l'identifiant du compte élève à ajouter :\n");
                __fpurge(stdin);
                fgets(identifiant, 50, stdin);
                identifiant[strcspn(identifiant, "\n")] = 0;
                printf("Saisissez le mot de passe du compte élève à ajouter :\n");
                __fpurge(stdin);
                fgets(mot_de_passe, 50, stdin);
                mot_de_passe[strcspn(mot_de_passe, "\n")] = 0;
                sprintf(requete, "INSERT INTO Eleve (ele_nom, ele_prenom, ele_identifiant, ele_motdepasse) VALUES ('%s', '%s', '%s', '%s')", nom, prenom, identifiant, mot_de_passe);
                if (mysql_query(con, requete))
                {
                    printf("Erreur !\n");
                }
                result = mysql_store_result(con);
                system("clear");
                printf("Compte élève ajouté !\n");
                mysql_free_result(result);
                break;
                //FIN AJOUT COMPTE ELEVE


            case 4:
                system("clear");
                printf("Déconnexion en cours...\n");
                quitter = 1;
                mysql_close(con);
                break;
            default:
                printf("Erreur d'exécution\n");

        }
    }while(quitter == 0);

}

void ajouterDansGroupe()
{
    int quitter = 0, choix;
    //INITIALISATION DE LA BDD
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        return(1);
    }

    if (mysql_real_connect(con, "localhost", "esigelec", "esigelec", "ProjetInfo", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Probleme de connexion\n");
        return(1);
    }
    MYSQL_RES *result;
    MYSQL_ROW row;
    int num_fields, id, groupe;
    char requete[100];
    //FIN INITIALISATION BDD

    do
    {
        printf("****************************************\n");
        printf("*                                      *\n");
        printf("*       AJOUTER DANS UN GROUPE         *\n");
        printf("*                                      *\n");
        printf("****************************************\n");
        printf("1 - Afficher les numeros de tous les élèves\n");
        printf("2 - Afficher les numéros de tous les enseignants\n");
        printf("3 - Lier un élève à un groupe\n");
        printf("4 - Lier un enseignant à un groupe\n");
        printf("5 - Quitter\n");
        printf("Faites votre choix\n");
        scanf("%d", &choix);
        switch(choix)
        {
            case 1:
                system("clear");
                if (mysql_query(con, "SELECT ele_id AS ID, ele_prenom AS Prenom, ele_nom AS Nom FROM Eleve"))
                {
                    return(1);
                }
                result = mysql_store_result(con);
                num_fields = mysql_num_fields(result);
                while ((row = mysql_fetch_row(result)))
                {
                    for(int i = 0; i < num_fields; i++)
                    {
                        printf("%s ", row[i] ? row[i] : "null");
                    }
                    printf("\n");
                }
                mysql_free_result(result);
                break;
            case 2:
                system("clear");
                if (mysql_query(con, "SELECT ens_id AS ID, ens_prenom AS Prenom, ens_nom AS Nom, ens_matiere AS Matiere FROM Enseignant"))
                {
                    printf("Erreur !\n");
                }
                result = mysql_store_result(con);
                num_fields = mysql_num_fields(result);
                while ((row = mysql_fetch_row(result)))
                {
                    for(int i = 0; i < num_fields; i++)
                    {
                        printf("%s ", row[i] ? row[i] : "null");
                    }
                    printf("\n");
                }
                mysql_free_result(result);
                break;
            case 3:
                system("clear");
                printf("Saisissez le numéro de l'élève :\n");
                scanf("%d", &id);
                printf("Saisissez le numéro du groupe :\n");
                scanf("%d", &groupe);
                system("clear");
                sprintf(requete, "INSERT INTO Est_dans_groupe (est_eleve, est_groupe) VALUES (%d, %d)", id, groupe);
                if (mysql_query(con, requete))
                {
                    printf("Erreur !\n");
                }
                if (result == NULL)
                {
                    fprintf(stderr, "Identifiant ou mot de passe incorrect\n");
                }
                printf("L'élève a bien été ajouté dans le groupe %d\n", groupe);
                break;
            case 4:
                system("clear");
                printf("Saisissez le numéro de l'enseignant :\n");
                scanf("%d", &id);
                printf("Saisissez le numéro du groupe :\n");
                scanf("%d", &groupe);
                system("clear");
                sprintf(requete, "INSERT INTO ens_dans (ens_dans_ens, ens_dans_grp) VALUES (%d, %d)", id, groupe);
                if (mysql_query(con, requete))
                {
                    printf("Erreur !\n");
                }
                if (result == NULL)
                {
                    fprintf(stderr, "Identifiant ou mot de passe incorrect\n");
                }
                printf("L'enseignant a bien été ajouté dans le groupe %d\n", groupe);
                break;
            case 5:
                system("clear");
                printf("Déconnexion en cours...\n");
                quitter = 1;
                break;
            default:
                system("clear");
                printf("Erreur d'exécution\n");

        }
    }while(quitter == 0);
}

void ajouterAppreciation(struct Compte compteEnseignant)
{
    char nom[50];
    char prenom[50];
    char requete[1000];
    char appreciation[300];
    int num_fields, annee;
    char id_eleve[10], id_enseignant[10], id_groupe[10], verif_groupe[10];
    //INITIALISATION DE LA BDD
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
    }

    if (mysql_real_connect(con, "localhost", "esigelec", "esigelec", "ProjetInfo", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Probleme de connexion\n");
    }
    MYSQL_RES *result;
    MYSQL_ROW row;
    //FIN INITIALISATION BDD
    __fpurge(stdin);

    //On obtient l'id de l'élève auquel on souhaite ajouter une appréciation
    printf("Saisissez le nom de l'élève :\n");
    fgets(nom, 50, stdin);
    __fpurge(stdin);
    nom[strcspn(nom, "\n")] = 0;
    printf("Saisissez le prenom de l'élève :\n");
    fgets(prenom, 50, stdin);
    __fpurge(stdin);
    prenom[strcspn(prenom, "\n")] = 0;
    sprintf(requete, "SELECT ele_id FROM Eleve WHERE ele_nom = '%s' AND ele_prenom = '%s'", nom, prenom);
    if (mysql_query(con, requete))
    {
        printf("Erreur !\n");
    }
    result = mysql_store_result(con);


    if (result == NULL)
    {
        fprintf(stderr, "Eleve non trouvé\n");
    }
    num_fields = mysql_num_fields(result);


    while ((row = mysql_fetch_row(result)))
    {
        strcpy(id_eleve, row[0]);
        printf("L'id de l'élève est : %s\n", id_eleve);
    }
    mysql_free_result(result);

    //On obtient l'id de l'enseignant
    sprintf(requete, "SELECT ens_id FROM Enseignant WHERE ens_nom = '%s' AND ens_prenom = '%s'", compteEnseignant.nom, compteEnseignant.prenom);
    if (mysql_query(con, requete))
    {
        printf("Erreur !\n");
    }
    result = mysql_store_result(con);


    if (result == NULL)
    {
        fprintf(stderr, "Enseignant non trouvé\n");
    }
    num_fields = mysql_num_fields(result);


    while ((row = mysql_fetch_row(result)))
    {
        strcpy(id_enseignant, row[0]);
        printf("L'id de l'enseignant est : %s\n", id_enseignant);
    }
    mysql_free_result(result);
    //On obtient maintenant l'id du groupe dans lequel est l'élève
    sprintf(requete, "SELECT est_groupe FROM Est_dans_groupe WHERE est_eleve = %s", id_eleve);
    if (mysql_query(con, requete))
    {
        printf("Erreur !\n");
    }
    result = mysql_store_result(con);


    if (result == NULL)
    {
        fprintf(stderr, "L'élève n'est dans aucun groupe\n");
    }
    num_fields = mysql_num_fields(result);


    while ((row = mysql_fetch_row(result)))
    {
        strcpy(id_groupe, row[0]);
        printf("L'élève est dans le groupe : %s\n", id_groupe);
    }
    mysql_free_result(result);

    //On verifie maintenant si l'enseignant qui essaye d'ajouter une appréciation a ce groupe en charge
    sprintf(requete, "SELECT ens_dans_grp FROM ens_dans WHERE ens_dans_ens = %s AND ens_dans_grp = %s", id_enseignant, id_groupe);
    if (mysql_query(con, requete))
    {
        printf("Erreur !\n");
    }
    result = mysql_store_result(con);


    if (result == NULL)
    {
        fprintf(stderr, "L'enseignant n'a pas ce groupe en charge\n");
        printf("Erreur !\n");
    }
    num_fields = mysql_num_fields(result);


    while ((row = mysql_fetch_row(result)))
    {
        strcpy(verif_groupe, row[0]);
        printf("L'enseignant enseigne dans le groupe : %s\n", verif_groupe);
    }
    mysql_free_result(result);
    //On peut maintenant entrer l'appréciation
    //Ca fait sans doute un peu bricolage mais ca permet d'être sur que l'enseignant a bien le groupe de l'élève en charge, j'avais des erreur en faisant autrement
    if(strcmp(id_groupe, verif_groupe) == 0)
    {
        printf("Vous avez bien cet élève en charge...\n");
        printf("Saisissez votre appréciation pour la matière %s :\n", compteEnseignant.matiere);
        __fpurge(stdin);
        fgets(appreciation, 300, stdin);
        __fpurge(stdin);
        appreciation[strcspn(appreciation, "\n")] = 0;
        printf("Saisissez l'année de l'appréciation :\n");
        scanf("%d", &annee);
        //On envoie maintenant la requete pour ajouter l'appréciation dans la base de données
        sprintf(requete, "INSERT INTO Appreciation (app_nom_eleve, app_prenom_eleve, app_nom_enseignant, app_prenom_enseignant, app_matiere, app_texte, app_annee, app_etat_validation) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', %d, 0)", nom, prenom, compteEnseignant.nom, compteEnseignant.prenom, compteEnseignant.matiere, appreciation, annee);
        if (mysql_query(con, requete))
        {
            printf("Erreur !\n");
        }
        result = mysql_store_result(con);
        system("clear");
        printf("Appréciation sauvegardée !\n");
        mysql_free_result(result);
    }
}

void modifierAppreciation(struct Compte compteEnseignant)
{
    //INITIALISATION DE LA BDD
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
    }

    if (mysql_real_connect(con, "localhost", "esigelec", "esigelec", "ProjetInfo", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Probleme de connexion\n");
    }
    MYSQL_RES *result;
    MYSQL_ROW row;
    //FIN INITIALISATION BDD

    char requete[1000], id_enseignant[50], nom_retourne[50], prenom_retourne[50], appreciation[500], id_validation[50];
    int num_fields, choix, i;
    system("clear");

    //On affiche toutes les appréciations modifiables par l'enseignant
    sprintf(requete, "SELECT app_id, app_nom_eleve, app_prenom_eleve, app_texte FROM Appreciation WHERE app_nom_enseignant = '%s' AND app_prenom_enseignant = '%s' AND app_etat_validation = 0", compteEnseignant.nom, compteEnseignant.prenom);
    if (mysql_query(con, requete))
    {
        printf("Erreur !\n");
    }
    result = mysql_store_result(con);
    num_fields = mysql_num_fields(result);
    printf("id | Nom | Prenom | Appréciation\n");
    //INSERT
    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s |", row[i] ? row[i] : "null");
        }
        printf("\n");
    }

    mysql_free_result(result);

    printf("Entrez l'id de l'appréciation à modifier :\n");
    scanf("%d", &choix);
    sprintf(requete, "SELECT app_nom_enseignant, app_prenom_enseignant, app_etat_validation FROM Appreciation WHERE app_id = %d", choix);
    if (mysql_query(con, requete))
    {
        printf("Erreur !\n");
    }
    result = mysql_store_result(con);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
    {
        strcpy(nom_retourne, row[0]);
        strcpy(prenom_retourne, row[1]);
        strcpy(id_validation, row[2]);
        printf("\n");
    }
    mysql_free_result(result);
    if(strcmp(compteEnseignant.nom, nom_retourne) == 0 && strcmp(compteEnseignant.prenom, prenom_retourne) == 0 && strcmp("0", id_validation) == 0)
    {
        printf("Entrez la nouvelle appréciation :\n");
        __fpurge(stdin);
        fgets(appreciation, 300, stdin);
        appreciation[strcspn(appreciation, "\n")] = 0;
        __fpurge(stdin);
        sprintf(requete, "UPDATE Appreciation SET app_texte = '%s' WHERE app_id = %d", appreciation, choix);
        if (mysql_query(con, requete))
        {
            printf("Erreur !\n");
        }
        result = mysql_store_result(con);
        num_fields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result)))
        {
            printf("\n");
        }
        mysql_free_result(result);
        system("clear");
        printf("Appréciation modifiée avec succès !\n");

    }



}

void voirAppreciation()
{
    //INITIALISATION DE LA BDD
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
    }

    if (mysql_real_connect(con, "localhost", "esigelec", "esigelec", "ProjetInfo", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Probleme de connexion\n");
    }
    MYSQL_RES *result;
    MYSQL_ROW row;
    int num_fields;
    char requete[100];
    //FIN INITIALISATION BDD

    if (mysql_query(con, "SELECT app_nom_enseignant, app_prenom_enseignant, app_nom_eleve, app_prenom_eleve, app_matiere, app_texte FROM Appreciation"))
    {
        return(1);
    }
    result = mysql_store_result(con);


    if (result == NULL)
    {
        fprintf(stderr, "Pas d'appréciations entrées\n");
    }
    num_fields = mysql_num_fields(result);

    system("clear");
    printf("Nom Enseignant | Prenom enseignant | Nom eleve | Prenom eleve | Matiere | Annee | Appreciation\n");
    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s |", row[i] ? row[i] : "null");
        }
        printf("\n");
    }
    mysql_free_result(result);
}

void validerAppreciation()
{
    //INITIALISATION DE LA BDD
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
    }

    if (mysql_real_connect(con, "localhost", "esigelec", "esigelec", "ProjetInfo", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Probleme de connexion\n");
    }
    MYSQL_RES *result;
    MYSQL_ROW row;
    int num_fields, choix;
    char requete[1000], nom_eleve[50], prenom_eleve[50], annee[10], prenom_bul[50];
    //FIN INITIALISATION BDD

    //Pour commencer, on afficher l'intégralité des appréciations en attente de validation
    if (mysql_query(con, "SELECT app_id, app_nom_enseignant, app_prenom_enseignant, app_nom_eleve, app_prenom_eleve, app_matiere, app_texte FROM Appreciation WHERE app_etat_validation = 0"))
    {
        printf("Erreur !\n");
    }
    result = mysql_store_result(con);


    if (result == NULL)
    {
        fprintf(stderr, "Pas d'appréciations en attente\n");
    }
    num_fields = mysql_num_fields(result);

    system("clear");
    printf("Id | Nom Enseignant | Prenom enseignant | Nom eleve | Prenom eleve | Matiere | Annee | Appreciation\n");
    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s |", row[i] ? row[i] : "null");
        }
        printf("\n");
    }
    mysql_free_result(result);
    printf("Saisissez l'id de l'appréciation à valider :\n");
    scanf("%d", &choix);


    sprintf(requete, "UPDATE Appreciation SET app_etat_validation = 1 WHERE app_id = %d", choix);
    if (mysql_query(con, requete))
    {
        printf("Erreur !\n");
    }

    system("clear");
    printf("Appréciation validée !\n");



}

void creerBulletin()
{
    //INITIALISATION DE LA BDD
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
    }

    if (mysql_real_connect(con, "localhost", "esigelec", "esigelec", "ProjetInfo", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Probleme de connexion\n");
    }
    MYSQL_RES *result;
    MYSQL_ROW row;
    //FIN INITIALISATION BDD

    char nom[50], prenom[50], requete[300];
    int annee;

    printf("Saisissez le nom de l'élève :\n");
    __fpurge(stdin);
    fgets(nom, 50, stdin);
    nom[strcspn(nom, "\n")] = 0;
    printf("Saisissez le prenom de l'élève :\n");
    __fpurge(stdin);
    fgets(prenom, 50, stdin);
    prenom[strcspn(prenom, "\n")] = 0;
    printf("Saisissez l'année du bulletin à créer :\n");
    scanf("%d", &annee);

    //On envoie maintenant la requete pour créer le bulletin
    sprintf(requete, "INSERT INTO Bulletin (bul_nom, bul_prenom, bul_annee) VALUES ('%s', '%s', %d)", nom, prenom, annee);
    if (mysql_query(con, requete))
    {
        printf("Erreur !\n");
    }
    result = mysql_store_result(con);
    system("clear");
    printf("Bulletin créé pour l'élève %s %s pour l'année %d !\n", prenom, nom, annee);
    mysql_free_result(result);

}

void afficherBulletin(char nomEleve[50], char prenomEleve[50])
{
    //INITIALISATION DE LA BDD
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
    }

    if (mysql_real_connect(con, "localhost", "esigelec", "esigelec", "ProjetInfo", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Probleme de connexion\n");
    }
    MYSQL_RES *result;
    MYSQL_ROW row;
    int num_fields, annee;
    char requete[1000];
    //FIN INITIALISATION BDD
    //On affiche deja les années des différents bulletins disponibles
    system("clear");
    printf("Voici les bulletins disponibles pour l'élève %s %s", prenomEleve, nomEleve);
    sprintf(requete, "SELECT bul_annee FROM Bulletin WHERE bul_nom = '%s' AND bul_prenom = '%s'", nomEleve, prenomEleve);
    if (mysql_query(con, requete))
    {
        return(1);
    }
    result = mysql_store_result(con);
    num_fields = mysql_num_fields(result);
    printf("Année |\n");
    //INSERT
    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s |", row[i] ? row[i] : "null");
        }
        printf("\n");
    }
    //On affiche maintenant toutes les appréciations validées de l'élève pour cette année
    mysql_free_result(result);
    printf("Saisissez l'année du bulletin à afficher :\n");
    scanf("%d", &annee);
    system("clear");

    sprintf(requete, "SELECT app_matiere, app_texte FROM Appreciation WHERE app_nom_eleve = '%s' AND app_prenom_eleve = '%s' AND app_annee = %d AND app_etat_validation = 1", nomEleve, prenomEleve, annee);
    if (mysql_query(con, requete))
    {
        printf("Erreur !\n");
    }
    result = mysql_store_result(con);
    num_fields = mysql_num_fields(result);
    printf("Voici les appréciations de %d pour l'élève %s %s:\n", annee, prenomEleve, nomEleve);
    printf("Matière | Appréciation\n");
    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s |", row[i] ? row[i] : "null");
        }
        printf("\n");
    }

    mysql_free_result(result);
}

int main()
{
    //INITIALISATION DE LA BDD
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        return(1);
    }

    if (mysql_real_connect(con, "localhost", "esigelec", "esigelec", "ProjetInfo", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "Probleme de connexion\n");
        return(1);
    }
    MYSQL_RES *result;
    MYSQL_ROW row;
    //FIN INITIALISATION BDD

    struct Compte infos_user;

    int quitter = 0, choix;
    char nom_utilisateur[50];
    char mot_de_passe[50];
    char requete[200];

    do
    {
        printf("****************************************\n");
        printf("*                                      *\n");
        printf("*     Gestionnaire d'appreciations     *\n");
        printf("*                                      *\n");
        printf("****************************************\n");
        printf("1 - Connexion Elève\n");
        printf("2 - Connexion Enseignant\n");
        printf("3 - Connexion Secrétariat\n");
        printf("4 - Quitter\n");
        printf("Faites votre choix\n");
        scanf("%d", &choix);
        switch(choix)
        {
        case 1:
            __fpurge(stdin);
            printf("Bonjour, Eleve...\n");
            printf("Saisissez votre nom d'utilisateur :\n");
            fgets(nom_utilisateur, 50, stdin);
            __fpurge(stdin);
            nom_utilisateur[strcspn(nom_utilisateur, "\n")] = 0; /* Retire le \n à la fin de la chaine pour éviter les erreurs de comparaison*/
            printf("\nSaisissez votre mot de passe :\n");
            fgets(mot_de_passe, 50, stdin);
            mot_de_passe[strcspn(mot_de_passe, "\n")] = 0; /*pareil*/
            sprintf(requete, "SELECT ele_nom, ele_prenom FROM Eleve WHERE ele_identifiant = '%s' AND ele_motdepasse = '%s'", nom_utilisateur, mot_de_passe);
            if (mysql_query(con, requete))
            {
                return(1);
            }
            result = mysql_store_result(con);


            if (result == NULL)
            {
                fprintf(stderr, "Identifiant ou mot de passe incorrect\n");
                return(1);
            }
            int num_fields = mysql_num_fields(result);


            while ((row = mysql_fetch_row(result)))
            {
                strcpy(infos_user.nom, row[0]);
                strcpy(infos_user.prenom, row[1]);
                strcpy(infos_user.identifiant, nom_utilisateur);
                strcpy(infos_user.mot_de_passe, mot_de_passe);
            }
                mysql_free_result(result);
                system("clear"); //Efface l'affichage pour éviter l'accumulation de texte, system("CLS") pour windows
                interfaceEleve(infos_user);
                infos_user = viderCompte(infos_user);

            break;
        case 2:
            __fpurge(stdin);
            printf("Bonjour, Enseignant...\n");
            printf("Saisissez votre nom d'utilisateur :\n");
            fgets(nom_utilisateur, 50, stdin);
            __fpurge(stdin);
            nom_utilisateur[strcspn(nom_utilisateur, "\n")] = 0; /* Retire le \n à la fin de la chaine pour éviter les erreurs de comparaison*/
            printf("\nSaisissez votre mot de passe :\n");
            fgets(mot_de_passe, 50, stdin);
            mot_de_passe[strcspn(mot_de_passe, "\n")] = 0; /*pareil*/
            sprintf(requete, "SELECT ens_nom, ens_prenom, ens_matiere FROM Enseignant WHERE ens_identifiant = '%s' AND ens_motdepasse = '%s'", nom_utilisateur, mot_de_passe);
            if (mysql_query(con, requete))
            {
                return(1);
            }
            result = mysql_store_result(con);

            if (result == NULL)
            {
                fprintf(stderr, "Identifiant ou mot de passe incorrect\n");
                return(1);
            }
            num_fields = mysql_num_fields(result);



            while ((row = mysql_fetch_row(result)))
            {
                strcpy(infos_user.nom, row[0]);
                strcpy(infos_user.prenom, row[1]);
                strcpy(infos_user.matiere, row[2]);
                strcpy(infos_user.identifiant, nom_utilisateur);
                strcpy(infos_user.mot_de_passe, mot_de_passe);
            }
            mysql_free_result(result);
            system("clear");
            interfaceEnseignant(infos_user);
            infos_user = viderCompte(infos_user);


            break;

        case 3:
            __fpurge(stdin);
            printf("Bonjour, Secretariat...\n");
            printf("Saisissez votre nom d'utilisateur :\n");
            fgets(nom_utilisateur, 50, stdin);
            __fpurge(stdin);
            nom_utilisateur[strcspn(nom_utilisateur, "\n")] = 0; /* Retire le \n à la fin de la chaine pour éviter les erreurs de comparaison*/
            printf("\nSaisissez votre mot de passe :\n");
            fgets(mot_de_passe, 50, stdin);
            mot_de_passe[strcspn(mot_de_passe, "\n")] = 0; /*pareil*/
            sprintf(requete, "SELECT sec_nom, sec_prenom FROM Secretariat WHERE sec_identifiant = '%s' AND sec_motdepasse = '%s'", nom_utilisateur, mot_de_passe);
            if (mysql_query(con, requete))
            {
                return(1);
            }
            result = mysql_store_result(con);

            if (result == NULL)
            {
                fprintf(stderr, "Identifiant ou mot de passe incorrect\n");
                return(1);
            }
            num_fields = mysql_num_fields(result);



            while ((row = mysql_fetch_row(result)))
            {
                strcpy(infos_user.nom, row[0]);
                strcpy(infos_user.prenom, row[1]);
                strcpy(infos_user.identifiant, nom_utilisateur);
                strcpy(infos_user.mot_de_passe, mot_de_passe);
            }
            mysql_free_result(result);
            system("clear");
            interfaceSecretariat(infos_user);
            infos_user = viderCompte(infos_user);

            break;
        case 4:
            quitter = 1;
            system("clear");
            printf("Au revoir...\n");
            break;
        default:
            system("clear");
            printf("Erreur d'execution\n");

        }
        mysql_close(con);
    }while (quitter == 0);
}
