# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#
require 'ffi'

require File.expand_path(File.join(File.dirname(__FILE__),"points"))


#
# Modulo para mapear los half_edge de C a Ruby, junto con sus funciones.
#
module HalfEdge
  extend FFI::Library
  ffi_lib "lib/libhalf_edge.so"

  class HalfEdge < FFI::Struct
    layout :first, Points::Point.by_ref, 
           :last, Points::Point.by_ref,
           :helper, Points::Point.by_ref,
           :twin, :pointer,
           :next, :pointer,
           :prev, :pointer,
           :incident_face, :pointer,
           :name, :string
  end

  attach_function :init_half_edge, [Points::Point.by_ref, Points::Point.by_ref, :string], HalfEdge.by_ref
  attach_function :destroy_half_edge, [HalfEdge.by_ref], :void
  attach_function :destroy_half_edge_with_points, [HalfEdge.by_ref], :void

  attach_function :he_intersection, [HalfEdge.by_ref, HalfEdge.by_ref], Points::Point.by_ref

  attach_function :copy_half_edge, [HalfEdge.by_ref], HalfEdge.by_ref 

  attach_function :cast_half_edge, [:pointer], HalfEdge.by_ref
end
