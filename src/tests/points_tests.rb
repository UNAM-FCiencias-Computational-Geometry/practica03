# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/points"))

#
# Reabre el modulo de Test para agregar la clase TestPoints, la cual
# tiene los test de las funciones de la estructura de C.
#
module Test
  class TestPoints

    # Public: Prueba la funcion que copia puntos que se le pasen.
    #
    # Examples
    #
    #     Test::TestPoints.create_copy_point
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.create_copy_point
      x = rand(2**27)
      y = rand(2**27)
      point = Points.init_point(x,y,"")
      point_copy = Points.create_copy_point(point)

      if not(point_copy.null?)
        result = point[:x] == point_copy[:x] and point[:y] == point_copy[:y]
      else
        result false
      end
        
      Points.destroy_point(point)
      Points.destroy_point(point_copy)
      
      result
    end
  end
end
