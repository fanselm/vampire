target_sources(vampire PRIVATE
    geom2.cpp
    geom.cpp
    global.cpp
    io.cpp
    libqhull.cpp
    mem.cpp
    merge.cpp
    poly2.cpp
    poly.cpp
    qhrandom.cpp
    qset.cpp
    qvoronoi.cpp
    rboxlib.cpp
    stat.cpp
    user.cpp
    usermem.cpp
    userprintf.cpp
    userprintf_rbox.cpp)

target_include_directories(vampire PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
