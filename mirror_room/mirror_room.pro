#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T22:33:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mirror_room
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    wallmodel.cpp \
    wall.cpp \
    wallmodeldelegate.cpp \
    wallgraphicsitem.cpp \
    areamodel.cpp \
    scene.cpp \
    areagraphicsitem.cpp \
    raygraphicsitem.cpp \
    wizardwelcome.cpp
#    glm/detail/dummy.cpp \
#    glm/detail/func_common.inl \
#    glm/detail/func_common_simd.inl \
#    glm/detail/func_exponential.inl \
#    glm/detail/func_exponential_simd.inl \
#    glm/detail/func_geometric.inl \
#    glm/detail/func_geometric_simd.inl \
#    glm/detail/func_integer.inl \
#    glm/detail/func_integer_simd.inl \
#    glm/detail/func_matrix.inl \
#    glm/detail/func_matrix_simd.inl \
#    glm/detail/func_packing.inl \
#    glm/detail/func_packing_simd.inl \
#    glm/detail/func_trigonometric.inl \
#    glm/detail/func_trigonometric_simd.inl \
#    glm/detail/func_vector_relational.inl \
#    glm/detail/func_vector_relational_simd.inl \
#    glm/detail/glm.cpp \
#    glm/detail/type_gentype.inl \
#    glm/detail/type_half.inl \
#    glm/detail/type_mat.inl \
#    glm/detail/type_mat2x2.inl \
#    glm/detail/type_mat2x3.inl \
#    glm/detail/type_mat2x4.inl \
#    glm/detail/type_mat3x2.inl \
#    glm/detail/type_mat3x3.inl \
#    glm/detail/type_mat3x4.inl \
#    glm/detail/type_mat4x2.inl \
#    glm/detail/type_mat4x3.inl \
#    glm/detail/type_mat4x4.inl \
#    glm/detail/type_mat4x4_simd.inl \
#    glm/detail/type_vec.inl \
#    glm/detail/type_vec1.inl \
#    glm/detail/type_vec2.inl \
#    glm/detail/type_vec3.inl \
#    glm/detail/type_vec4.inl \
#    glm/detail/type_vec4_simd.inl \
#    glm/gtc/bitfield.inl \
#    glm/gtc/color_encoding.inl \
#    glm/gtc/color_space.inl \
#    glm/gtc/constants.inl \
#    glm/gtc/epsilon.inl \
#    glm/gtc/functions.inl \
#    glm/gtc/integer.inl \
#    glm/gtc/matrix_access.inl \
#    glm/gtc/matrix_inverse.inl \
#    glm/gtc/matrix_transform.inl \
#    glm/gtc/noise.inl \
#    glm/gtc/packing.inl \
#    glm/gtc/quaternion.inl \
#    glm/gtc/quaternion_simd.inl \
#    glm/gtc/random.inl \
#    glm/gtc/reciprocal.inl \
#    glm/gtc/round.inl \
#    glm/gtc/type_precision.inl \
#    glm/gtc/type_ptr.inl \
#    glm/gtc/ulp.inl \
#    glm/gtc/vec1.inl \
#    glm/gtx/associated_min_max.inl \
#    glm/gtx/bit.inl \
#    glm/gtx/closest_point.inl \
#    glm/gtx/color_space.inl \
#    glm/gtx/color_space_YCoCg.inl \
#    glm/gtx/common.inl \
#    glm/gtx/compatibility.inl \
#    glm/gtx/component_wise.inl \
#    glm/gtx/dual_quaternion.inl \
#    glm/gtx/euler_angles.inl \
#    glm/gtx/extend.inl \
#    glm/gtx/extended_min_max.inl \
#    glm/gtx/fast_exponential.inl \
#    glm/gtx/fast_square_root.inl \
#    glm/gtx/fast_trigonometry.inl \
#    glm/gtx/float_notmalize.inl \
#    glm/gtx/gradient_paint.inl \
#    glm/gtx/handed_coordinate_space.inl \
#    glm/gtx/hash.inl \
#    glm/gtx/integer.inl \
#    glm/gtx/intersect.inl \
#    glm/gtx/io.inl \
#    glm/gtx/log_base.inl \
#    glm/gtx/matrix_cross_product.inl \
#    glm/gtx/matrix_decompose.inl \
#    glm/gtx/matrix_interpolation.inl \
#    glm/gtx/matrix_major_storage.inl \
#    glm/gtx/matrix_operation.inl \
#    glm/gtx/matrix_query.inl \
#    glm/gtx/matrix_transform_2d.inl \
#    glm/gtx/mixed_product.inl \
#    glm/gtx/norm.inl \
#    glm/gtx/normal.inl \
#    glm/gtx/normalize_dot.inl \
#    glm/gtx/number_precision.inl \
#    glm/gtx/optimum_pow.inl \
#    glm/gtx/orthonormalize.inl \
#    glm/gtx/perpendicular.inl \
#    glm/gtx/polar_coordinates.inl \
#    glm/gtx/projection.inl \
#    glm/gtx/quaternion.inl \
#    glm/gtx/raw_data.inl \
#    glm/gtx/rotate_normalized_axis.inl \
#    glm/gtx/rotate_vector.inl \
#    glm/gtx/scalar_relational.inl \
#    glm/gtx/simd_mat4.inl \
#    glm/gtx/simd_quat.inl \
#    glm/gtx/simd_vec4.inl \
#    glm/gtx/spline.inl \
#    glm/gtx/std_based_type.inl \
#    glm/gtx/string_cast.inl \
#    glm/gtx/transform.inl \
#    glm/gtx/transform2.inl \
#    glm/gtx/type_aligned.inl \
#    glm/gtx/type_trait.inl \
#    glm/gtx/vector_angle.inl \
#    glm/gtx/vector_query.inl \
#    glm/gtx/wrap.inl

HEADERS  += mainwindow.h \
    wallmodel.h \
    wall.h \
    wallmodeldelegate.h \
    wallgraphicsitem.h \
    areamodel.h \
    scene.h \
    areagraphicsitem.h \
    raygraphicsitem.h \
    extensions.h \
    wizardwelcome.h
#    glm/detail/_features.hpp \
#    glm/detail/_fixes.hpp \
#    glm/detail/_noise.hpp \
#    glm/detail/_swizzle.hpp \
#    glm/detail/_swizzle_func.hpp \
#    glm/detail/_vectorize.hpp \
#    glm/detail/func_common.hpp \
#    glm/detail/func_exponential.hpp \
#    glm/detail/func_geometric.hpp \
#    glm/detail/func_integer.hpp \
#    glm/detail/func_matrix.hpp \
#    glm/detail/func_packing.hpp \
#    glm/detail/func_trigonometric.hpp \
#    glm/detail/func_vector_relational.hpp \
#    glm/detail/precision.hpp \
#    glm/detail/setup.hpp \
#    glm/detail/type_float.hpp \
#    glm/detail/type_gentype.hpp \
#    glm/detail/type_half.hpp \
#    glm/detail/type_int.hpp \
#    glm/detail/type_mat.hpp \
#    glm/detail/type_mat2x2.hpp \
#    glm/detail/type_mat2x3.hpp \
#    glm/detail/type_mat2x4.hpp \
#    glm/detail/type_mat3x2.hpp \
#    glm/detail/type_mat3x3.hpp \
#    glm/detail/type_mat3x4.hpp \
#    glm/detail/type_mat4x2.hpp \
#    glm/detail/type_mat4x3.hpp \
#    glm/detail/type_mat4x4.hpp \
#    glm/detail/type_vec.hpp \
#    glm/detail/type_vec1.hpp \
#    glm/detail/type_vec2.hpp \
#    glm/detail/type_vec3.hpp \
#    glm/detail/type_vec4.hpp \
#    glm/gtc/bitfield.hpp \
#    glm/gtc/color_space.hpp \
#    glm/gtc/constants.hpp \
#    glm/gtc/epsilon.hpp \
#    glm/gtc/functions.hpp \
#    glm/gtc/integer.hpp \
#    glm/gtc/matrix_access.hpp \
#    glm/gtc/matrix_integer.hpp \
#    glm/gtc/matrix_inverse.hpp \
#    glm/gtc/matrix_transform.hpp \
#    glm/gtc/noise.hpp \
#    glm/gtc/packing.hpp \
#    glm/gtc/quaternion.hpp \
#    glm/gtc/random.hpp \
#    glm/gtc/reciprocal.hpp \
#    glm/gtc/round.hpp \
#    glm/gtc/type_aligned.hpp \
#    glm/gtc/type_precision.hpp \
#    glm/gtc/type_ptr.hpp \
#    glm/gtc/ulp.hpp \
#    glm/gtc/vec1.hpp \
#    glm/gtx/associated_min_max.hpp \
#    glm/gtx/bit.hpp \
#    glm/gtx/closest_point.hpp \
#    glm/gtx/color_space.hpp \
#    glm/gtx/color_space_YCoCg.hpp \
#    glm/gtx/common.hpp \
#    glm/gtx/compatibility.hpp \
#    glm/gtx/component_wise.hpp \
#    glm/gtx/dual_quaternion.hpp \
#    glm/gtx/euler_angles.hpp \
#    glm/gtx/extend.hpp \
#    glm/gtx/extended_min_max.hpp \
#    glm/gtx/fast_exponential.hpp \
#    glm/gtx/fast_square_root.hpp \
#    glm/gtx/fast_trigonometry.hpp \
#    glm/gtx/gradient_paint.hpp \
#    glm/gtx/handed_coordinate_space.hpp \
#    glm/gtx/hash.hpp \
#    glm/gtx/integer.hpp \
#    glm/gtx/intersect.hpp \
#    glm/gtx/io.hpp \
#    glm/gtx/log_base.hpp \
#    glm/gtx/matrix_cross_product.hpp \
#    glm/gtx/matrix_decompose.hpp \
#    glm/gtx/matrix_interpolation.hpp \
#    glm/gtx/matrix_major_storage.hpp \
#    glm/gtx/matrix_operation.hpp \
#    glm/gtx/matrix_query.hpp \
#    glm/gtx/matrix_transform_2d.hpp \
#    glm/gtx/mixed_product.hpp \
#    glm/gtx/norm.hpp \
#    glm/gtx/normal.hpp \
#    glm/gtx/normalize_dot.hpp \
#    glm/gtx/number_precision.hpp \
#    glm/gtx/optimum_pow.hpp \
#    glm/gtx/orthonormalize.hpp \
#    glm/gtx/perpendicular.hpp \
#    glm/gtx/polar_coordinates.hpp \
#    glm/gtx/projection.hpp \
#    glm/gtx/quaternion.hpp \
#    glm/gtx/range.hpp \
#    glm/gtx/raw_data.hpp \
#    glm/gtx/rotate_normalized_axis.hpp \
#    glm/gtx/rotate_vector.hpp \
#    glm/gtx/scalar_multiplication.hpp \
#    glm/gtx/scalar_relational.hpp \
#    glm/gtx/simd_mat4.hpp \
#    glm/gtx/simd_quat.hpp \
#    glm/gtx/simd_vec4.hpp \
#    glm/gtx/spline.hpp \
#    glm/gtx/std_based_type.hpp \
#    glm/gtx/string_cast.hpp \
#    glm/gtx/transform.hpp \
#    glm/gtx/transform2.hpp \
#    glm/gtx/type_aligned.hpp \
#    glm/gtx/type_trait.hpp \
#    glm/gtx/vector_angle.hpp \
#    glm/gtx/vector_query.hpp \
#    glm/gtx/wrap.hpp \
#    glm/simd/common.h \
#    glm/simd/exponential.h \
#    glm/simd/geometric.h \
#    glm/simd/integer.h \
#    glm/simd/matrix.h \
#    glm/simd/packing.h \
#    glm/simd/platform.h \
#    glm/simd/trigonometric.h \
#    glm/simd/vector_relational.h \
#    glm/common.hpp \
#    glm/exponential.hpp \
#    glm/ext.hpp \
#    glm/fwd.hpp \
#    glm/geometric.hpp \
#    glm/glm.hpp \
#    glm/integer.hpp \
#    glm/mat2x2.hpp \
#    glm/mat2x3.hpp \
#    glm/mat2x4.hpp \
#    glm/mat3x2.hpp \
#    glm/mat3x3.hpp \
#    glm/mat3x4.hpp \
#    glm/mat4x2.hpp \
#    glm/mat4x3.hpp \
#    glm/mat4x4.hpp \
#    glm/matrix.hpp \
#    glm/packing.hpp \
#    glm/trigonometric.hpp \
#    glm/vec2.hpp \
#    glm/vec3.hpp \
#    glm/vec4.hpp \
#    glm/vector_relational.hpp

FORMS    += mainwindow.ui \
    wizardwelcome.ui

RESOURCES += \
    icons.qrc
