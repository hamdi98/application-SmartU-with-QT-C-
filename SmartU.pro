#-------------------------------------------------
#
# Project created by QtCreator 2018-12-02T15:26:27
#
#-------------------------------------------------

QT       += core gui sql charts printsupport network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartU
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        login.cpp \
    mainwindow.cpp \
    connection.cpp \
    acceuil.cpp \
    demande.cpp \
    materiel.cpp \
    recu.cpp \
    staff.cpp \
    demandestaff.cpp \
    personne.cpp \
    demandeenseignant.cpp \
    enseignant.cpp \
    niveauclasse.cpp \
    cafeteriaadmin.cpp \
    buvette.cpp \
    produit.cpp \
    ajout_produit.cpp \
    arduino.cpp \
    cafeteriaactualadmin.cpp \
    abonnement.cpp \
    gererabonnement.cpp \
    gestionemprunt.cpp \
    emprunt.cpp \
    place2.cpp \
    abonnep.cpp \
    demande_parking.cpp \
    gerer_abonnep.cpp \
    place.cpp \
    etudiantt.cpp \
    foyer.cpp \
    foyerui.cpp \
    smtp.cpp

HEADERS += \
        login.h \
    mainwindow.h \
    connection.h \
    acceuil.h \
    demande.h \
    materiel.h \
    recu.h \
    staff.h \
    demandestaff.h \
    personne.h \
    demandeenseignant.h \
    enseignant.h \
    niveauclasse.h \
    cafeteriaadmin.h \
    buvette.h \
    produit.h \
    ajout_produit.h \
    arduino.h \
    cafeteriaactualadmin.h \
    abonnement.h \
    gererabonnement.h \
    gestionemprunt.h \
    emprunt.h \
    place2.h \
    abonnep.h \
    demande_parking.h \
    gerer_abonnep.h \
    place.h \
    etudiantt.h \
    foyer.h \
    foyerui.h \
    smtp.h

FORMS += \
        login.ui \
    mainwindow.ui \
    acceuil.ui \
    demandestaff.ui \
    demandeenseignant.ui \
    enseignant.ui \
    niveauclasse.ui \
    cafeteriaadmin.ui \
    ajout_produit.ui \
    cafeteriaactualadmin.ui \
    gererabonnement.ui \
    gestionemprunt.ui \
    place2.ui \
    gerer_abonnep.ui \
    etudiantt.ui \
    foyerui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
