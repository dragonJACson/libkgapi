set(kgapiblogger_SRCS
    blog.cpp
    blogfetchjob.cpp
    bloggerservice.cpp
    comment.cpp
    commentapprovejob.cpp
    commentdeletecontentjob.cpp
    commentdeletejob.cpp
    commentfetchjob.cpp
    page.cpp
    pagecreatejob.cpp
    pagedeletejob.cpp
    pagefetchjob.cpp
    pagemodifyjob.cpp
    post.cpp
    postcreatejob.cpp
    postdeletejob.cpp
    postfetchjob.cpp
    postmodifyjob.cpp
    postpublishjob.cpp
    postsearchjob.cpp

    ../debug.cpp
)

ecm_generate_headers(kgapiblogger_CamelCase_HEADERS
    HEADER_NAMES
    Blog
    BlogFetchJob
    Comment
    CommentApproveJob
    CommentDeleteContentJob
    CommentDeleteJob
    CommentFetchJob
    Page
    PageCreateJob
    PageDeleteJob
    PageFetchJob
    PageModifyJob
    Post
    PostCreateJob
    PostDeleteJob
    PostFetchJob
    PostModifyJob
    PostPublishJob
    PostSearchJob
    PREFIX KGAPI/Blogger
    REQUIRED_HEADERS kgapiblogger_HEADERS
)

add_library(KPimGAPIBlogger
    ${kgapiblogger_SRCS}
)

generate_export_header(KPimGAPIBlogger BASE_NAME kgapiblogger)

add_library(KPim::GAPIBlogger ALIAS KPimGAPIBlogger)
# TODO: Backwards compatibility, remove in next major release
add_library(KF5::GAPIBlogger ALIAS KPimGAPIBlogger)
target_include_directories(KPimGAPIBlogger INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim/KGAPI>")

target_link_libraries(KPimGAPIBlogger
PUBLIC
    KPim::GAPICore
PRIVATE
    Qt5::Network
)

set_target_properties(KPimGAPIBlogger PROPERTIES
    VERSION ${KGAPI_VERSION_STRING}
    SOVERSION ${KGAPI_SOVERSION}
    EXPORT_NAME GAPIBlogger
)

install(TARGETS
    KPimGAPIBlogger
    EXPORT KPimGAPITargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

install(FILES
    ${kgapiblogger_CamelCase_HEADERS}
    DESTINATION "${KDE_INSTALL_INCLUDEDIR}/KPim/KGAPI/KGAPI/Blogger"
    COMPONENT Devel
)

install(FILES
    ${kgapiblogger_HEADERS}
    "${CMAKE_CURRENT_BINARY_DIR}/kgapiblogger_export.h"
    DESTINATION "${KDE_INSTALL_INCLUDEDIR}/KPim/KGAPI/kgapi/blogger"
    COMPONENT Devel
)

ecm_generate_pri_file(BASE_NAME KGAPIBlogger
    LIB_NAME KPimGAPIBlogger
    DEPS "GAPICore"
    FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR "${KDE_INSTALL_INCLUDEDIR}/KPim/KGAPI"
)

install(FILES
    "${PRI_FILENAME}"
    DESTINATION "${ECM_MKSPECS_INSTALL_DIR}"
)
