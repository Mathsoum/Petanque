project(petanque)
FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

SET(petanque_SOURCES main.cpp
					mainwindow.cpp
					team.cpp
					teammodel.cpp
					)

SET(petanque_test_SOURCES
					team.cpp
					teammodel.cpp
					testteammodel.cpp
					)

SET(petanque_HEADERS
				mainwindow.h
				team.h
				teammodel.h
				)

SET(petanque_test_HEADERS
					team.h
					teammodel.h
					testteammodel.h
					)

SET(petanque_FORMS mainwindow.ui)

QT4_WRAP_CPP(petanque_HEADERS_MOC ${petanque_HEADERS})
QT4_WRAP_UI(petanque_FORMS_HEADERS ${petanque_FORMS})

QT4_WRAP_CPP(petanque_test_HEADERS_MOC ${petanque_test_HEADERS})

set(QT_USE_QTTEST TRUE)

add_executable(petanque
			${petanque_SOURCES}
			${petanque_HEADERS_MOC}
			${petanque_FORMS_HEADERS}
			)

add_executable(test_petanque
			${petanque_test_SOURCES}
			${petanque_test_HEADERS_MOC}
			)


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(test_petanque ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES})
target_link_libraries(petanque ${QT_LIBRARIES})

