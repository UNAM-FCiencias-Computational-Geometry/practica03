# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#
require 'ffi'

require File.expand_path(File.join(File.dirname(__FILE__),"points"))
require File.expand_path(File.join(File.dirname(__FILE__),"half_edge"))

#
# Modulo para mapear la lista doblemente ligada y sus funciones de C a Ruby
#
module List
  extend FFI::Library
  ffi_lib "lib/libdouble_linked_list.so"

  Item_type = enum(:point, 1,
                   :half_edge,
                   :face)

  class List < FFI::Struct
    layout :head, :pointer,
           :tail, :pointer,
           :size, :int,
           :element, Item_type
  end

  attach_function :init_double_linked_list, [Item_type], List.by_ref
  attach_function :destroy_double_linked_list, [List.by_ref], :void
  
  attach_function :push_back, [List.by_ref, :pointer], :void
  attach_function :push_front, [List.by_ref, :pointer], :void

  attach_function :empty_list, [List.by_ref], :int

  attach_function :pop_back, [List.by_ref], :pointer
  attach_function :pop_front, [List.by_ref], :pointer
  
  attach_function :pick_back, [List.by_ref], :pointer
  attach_function :pick_front, [List.by_ref], :pointer

  # Public: Convierte una lista de puntos de intersecicon 
  # de C a un arreglo de Ruby.
  # 
  # list - La lista que se quiere convertir a un arreglo.
  # 
  # Examples
  #    
  #     List.to_a((1,2),(2,4)) Recuerda que la entrada es una lista de C.
  #     # => [[1,2],[2,4]]
  #
  # Regresa un arreglo
  def self.to_a(list)
    array = Array.new
    while list[:size] != 0   
      point = Points.to_a(cast_point(pop_front(list)))

      point[2] = cast_half_edge(point[2])
      point[3] = cast_half_edge(point[3])

      point[2] = [[point[2][:first][:x],
                   point[2][:first][:y]],
                  [point[2][:last][:x],
                   point[2][:last][:y]]]
      
      point[3] = [[point[3][:first][:x],
                   point[3][:first][:y]],
                  [point[3][:last][:x],
                   point[3][:last][:y]]]
      
      array << point
    end
    array
  end  
end
