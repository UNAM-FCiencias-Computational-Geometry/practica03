# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/make_monotone"))
require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/dcel"))

module Test
  class TestMonotone
    
    # Public: Convierte  una lista aristas o caras a un arreglo de Ruby
    #         de strings que contiene los nombres de las aristas o las caras.
    def self.list_to_a(list,type)      

      return [] if list.null?
      
      element = List.pop_front(list)
      result = []
      while not(element.null?)
        if (type == "HALF_EDGE")
          half_edge = HalfEdge.cast_half_edge(element)
          
          result << half_edge
          
          element = List.pop_front(list)
          
        end
      end
      
      return result
    end

    # Public: Obtiene todas las caras de la DCEL que se le pase.
    def self.get_all_faces(dcel)
      faces = RBTree.rb_tree_to_list(dcel[:face])

      faces_array = []
      while (List.empty_list(faces) == 0) 
        faces_array << Face.cast_face(List.pop_front(faces))
      end

      return faces_array.keep_if {|face| face[:name] != "face 1"}
    end

    # Public: Prueba que el poligono que se le pase sea monotono.
    #
    # Examples
    #
    #     Test::TestMonotone.is_monotone(poligon)
    #     # => true
    # 
    # Regresa true si el poligono es monotono, false en caso contrario
    def self.is_monotone(poligon)
      
      poligon.each {
          |half_edge|
          
          vertex = half_edge[:first]
          vertex_type = Monotone.calculate_vertex_type(vertex)
          count_start = 0
          count_end = 0
          
          if (vertex_type == :regular) 
          elsif (vertex_type == :start)
            count_start += 1
            if (count_start > 1)
              return false
            end
          elsif (vertex_type == :end)
            count_end += 1
            if (count_end > 1)
              return false
            end
          else
            return false
          end
        }

    end
    

    # Public: Prueba la funcion make_monotone de algorithms/make_monotone.c
    #
    # Examples
    #
    #     Test::TestMonotone.make_monotone
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.make_monotone
      dcel = ExampleDCEL.construct_example
      Monotone.make_monotone(dcel)
      
      faces = self.get_all_faces(dcel)
      
      monotone_pieces = []

      faces.each { 
          |face|
          monotone_pieces << self.list_to_a(DCEL.incident_he_to_f(face),"HALF_EDGE")
        }

      monotone_pieces.each {
          |poligon|
          return false if not(self.is_monotone(poligon))
        }
      
      return true
    end
  end
end

