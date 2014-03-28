# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#
require 'ffi'

#
# Modulo para mapear los puntos en 2d de C a Ruby, junto con sus funciones.
#
module Points
  extend FFI::Library
  ffi_lib "lib/lib2d_points.so"

  class Point < FFI::Struct
    layout :x, :double,
           :y, :double,
           :incident_edge, :pointer,
           :name, :string,
           :half_edge, :pointer,
           :intersection, :pointer
  end
  
  attach_function :init_point_empty, [], Point.by_ref
  attach_function :init_point, [:double,:double, :string], Point.by_ref

  attach_function :create_copy_point, [Point.by_ref], Point.by_ref
  attach_function :destroy_point, [Point.by_ref], :void

  attach_function :curve_orientation, [Point.by_ref,Point.by_ref,Point.by_ref], :int

  attach_function :cast_point, [:pointer], Point.by_ref

  # Public: Convierte un punto de C a un arreglo de dos enteros y
  # segmentos de Ruby.
  #
  # point - El punto que se quiere convertir.
  #
  # Examples
  #
  #     Points.to_a((1,2)) Recuerda que la entrada es un punto de C.
  #     # => [1,2]
  #
  # Regresa un arreglo de dos enteros
  def self.to_a(point)
    if (point.null?) then
      []
    else
      [point[:x], point[:y], point[:name]]
    end
  end

end
