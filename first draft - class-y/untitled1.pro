QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_course_to_prof.cpp \
    addnewcourse.cpp \
    addnewprof.cpp \
    addnewstudent.cpp \
    addstudenttoclass.cpp \
    adminCLASS.cpp \
    course.cpp \
    main.cpp \
    mainwindow.cpp \
    profsclass.cpp \
    set_class_grade_dialogue.cpp \
    studentsclass.cpp

HEADERS += \
    add_course_to_prof.h \
    addnewcourse.h \
    addnewprof.h \
    addnewstudent.h \
    addstudenttoclass.h \
    adminCLASS.h \
    course.h \
    mainwindow.h \
    profsclass.h \
    set_class_grade_dialogue.h \
    studentsclass.h

FORMS += \
    add_course_to_prof.ui \
    addnewcourse.ui \
    addnewprof.ui \
    addnewstudent.ui \
    addstudenttoclass.ui \
    mainwindow.ui \
    set_class_grade_dialogue.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
