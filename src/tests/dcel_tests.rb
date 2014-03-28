# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/dcel"))

#
# Reabre el modulo de Test para agregar la clase TestList, 
# la cual tiene los test de las funciones la estructura de C correspondiente.
#
module Test
  class TestDCEL
    
    # Public: Convierte  una lista aristas o caras a un arreglo de Ruby
    #         de strings que contiene los nombres de las aristas o las caras.
    def self.list_to_a(list,type)      
      return [] if list.null?
      
      element = List.pop_front(list)
      result = []
      while not(element.null?)
        if (type == "HALF_EDGE")
          result << HalfEdge.cast_half_edge(element)[:name]
        end
        
        if (type == "FACE")
          result << Face.cast_face(element)[:name]
        end
        element = List.pop_front(list)
      end
      
      return result.sort{|x,y| x<=>y}
    end
    
    # Public: Prueba la funcion de incident_he_to_v, obtiene los resultados
    #         del ejemplo y los compara con los resultados que ya sabemos debe
    #         de obtener.
    # Examples
    #  
    #    Test::TestDCEL.incident_he_to_v
    #    # => true
    # Regresa true si la funcion en C responde de forma correcta o false en caso
    # contrario
    def self.incident_he_to_v      
      dcel = ExampleDCEL.construct_example;

      a = Points.init_point(1.to_f,1.to_f,"")
      b = Points.init_point(13.to_f,1.to_f,"")
      c = Points.init_point(1.to_f,9.to_f,"")
      d = Points.init_point(13.to_f,9.to_f,"")
      e = Points.init_point(3.to_f,3.to_f,"")
      f = Points.init_point(4.to_f,5.to_f,"")
      g = Points.init_point(3.to_f,7.to_f,"")
      h = Points.init_point(6.to_f,7.to_f,"")
      i = Points.init_point(5.to_f,4.to_f,"")
      j = Points.init_point(8.to_f,2.to_f,"")
      k = Points.init_point(10.to_f,5.to_f,"")
      l = Points.init_point(11.to_f,4.to_f,"")
      m = Points.init_point(11.to_f,2.to_f,"")

      original_a = Points.cast_point(RBTree.rb_search(dcel[:vertex], a))
      original_b = Points.cast_point(RBTree.rb_search(dcel[:vertex], b))
      original_c = Points.cast_point(RBTree.rb_search(dcel[:vertex], c))
      original_d = Points.cast_point(RBTree.rb_search(dcel[:vertex], d))
      original_e = Points.cast_point(RBTree.rb_search(dcel[:vertex], e))
      original_f = Points.cast_point(RBTree.rb_search(dcel[:vertex], f))
      original_g = Points.cast_point(RBTree.rb_search(dcel[:vertex], g))
      original_h = Points.cast_point(RBTree.rb_search(dcel[:vertex], h))
      original_i = Points.cast_point(RBTree.rb_search(dcel[:vertex], i))
      original_j = Points.cast_point(RBTree.rb_search(dcel[:vertex], j))
      original_k = Points.cast_point(RBTree.rb_search(dcel[:vertex], k))
      original_l = Points.cast_point(RBTree.rb_search(dcel[:vertex], l))      
      original_m = Points.cast_point(RBTree.rb_search(dcel[:vertex], m))

      result_a = list_to_a(DCEL.incident_he_to_v(original_a), "HALF_EDGE")
      result_b = list_to_a(DCEL.incident_he_to_v(original_b), "HALF_EDGE")
      result_c = list_to_a(DCEL.incident_he_to_v(original_c), "HALF_EDGE")
      result_d = list_to_a(DCEL.incident_he_to_v(original_d), "HALF_EDGE")
      result_e = list_to_a(DCEL.incident_he_to_v(original_e), "HALF_EDGE")
      result_f = list_to_a(DCEL.incident_he_to_v(original_f), "HALF_EDGE")
      result_g = list_to_a(DCEL.incident_he_to_v(original_g), "HALF_EDGE")
      result_h = list_to_a(DCEL.incident_he_to_v(original_h), "HALF_EDGE")
      result_i = list_to_a(DCEL.incident_he_to_v(original_i), "HALF_EDGE")
      result_j = list_to_a(DCEL.incident_he_to_v(original_j), "HALF_EDGE")
      result_k = list_to_a(DCEL.incident_he_to_v(original_k), "HALF_EDGE")
      result_l = list_to_a(DCEL.incident_he_to_v(original_l), "HALF_EDGE")
      result_m = list_to_a(DCEL.incident_he_to_v(original_m), "HALF_EDGE")

      return false if ["a","b'"].sort{|x,y| x<=>y } != result_a
      return false if ["c","a'"].sort{|x,y| x<=>y } != result_b
      return false if ["b","d'"].sort{|x,y| x<=>y } != result_c
      return false if ["d","c'"].sort{|x,y| x<=>y } != result_d
      return false if ["e'","h'","f"].sort{|x,y| x<=>y } != result_e
      return false if ["l","g'","h","i'"].sort{|x,y| x<=>y } != result_f
      return false if ["j'","i","e"].sort{|x,y| x<=>y } != result_g
      return false if ["j","l'","k'"].sort{|x,y| x<=>y } != result_h
      return false if ["k","g","f'"].sort{|x,y| x<=>y } != result_i
      return false if ["q","m'"].sort{|x,y| x<=>y } != result_j
      return false if ["m","n'"].sort{|x,y| x<=>y } != result_k
      return false if ["n","p'"].sort{|x,y| x<=>y } != result_l
      return false if ["q'","p"].sort{|x,y| x<=>y } != result_m

      return true
    end
   
     
    # Public: Prueba la funcion de incident_f_to_f, obtiene los resultados
    #         del ejemplo y los compara con los resultados que ya sabemos debe
    #         de obtener.
    # Examples
    #  
    #    Test::TestDCEL.incident_f_to_f
    #    # => true
    # Regresa true si la funcion en C responde de forma correcta o false en caso
    # contrario
    def self.incident_f_to_f
       dcel = ExampleDCEL.construct_example;

       f1 = Face.init_face("face 1",nil, nil)
       f2 = Face.init_face("face 2",nil, nil)
       f3 = Face.init_face("face 3",nil, nil)
       f4 = Face.init_face("face 4",nil, nil)
       f5 = Face.init_face("face 5",nil, nil)
       f6 = Face.init_face("face 6",nil, nil)
       f7 = Face.init_face("face 7",nil, nil)

       original_f1 = Face.cast_face(RBTree.rb_search(dcel[:face],f1))
       original_f2 = Face.cast_face(RBTree.rb_search(dcel[:face],f2))
       original_f3 = Face.cast_face(RBTree.rb_search(dcel[:face],f3))
       original_f4 = Face.cast_face(RBTree.rb_search(dcel[:face],f4))
       original_f5 = Face.cast_face(RBTree.rb_search(dcel[:face],f5))
       original_f6 = Face.cast_face(RBTree.rb_search(dcel[:face],f6))
       original_f7 = Face.cast_face(RBTree.rb_search(dcel[:face],f7))

       result_f1 = list_to_a(DCEL.incident_f_to_f(original_f1),"FACE")
       result_f2 = list_to_a(DCEL.incident_f_to_f(original_f2),"FACE")
       result_f3 = list_to_a(DCEL.incident_f_to_f(original_f3),"FACE")
       result_f4 = list_to_a(DCEL.incident_f_to_f(original_f4),"FACE")
       result_f5 = list_to_a(DCEL.incident_f_to_f(original_f5),"FACE")
       result_f6 = list_to_a(DCEL.incident_f_to_f(original_f6),"FACE")
       result_f7 = list_to_a(DCEL.incident_f_to_f(original_f7),"FACE")

       return false if  ["face 2"].sort{ |x,y| x<=>y } != result_f1
       return false if  ["face 1","face 3","face 4","face 5","face 6","face 7"].sort{ |x,y| x<=>y } != result_f2
       return false if  ["face 2"].sort{ |x,y| x<=>y } != result_f3
       return false if  ["face 6", "face 5", "face 2"].sort{ |x,y| x<=>y } != result_f4
       return false if  ["face 4", "face 7", "face 2"].sort{ |x,y| x<=>y } != result_f5
       return false if  ["face 7", "face 4", "face 2"].sort{ |x,y| x<=>y } != result_f6
       return false if  ["face 6", "face 5", "face 2"].sort{ |x,y| x<=>y } != result_f7
       
       return true
       
    end
    
     
    # Public: Prueba la funcion de incident_he_to_f, obtiene los resultados
    #         del ejemplo y los compara con los resultados que ya sabemos debe
    #         de obtener.
    # Examples
    #  
    #    Test::TestDCEL.incident_he_to_f
    #    # => true
    # Regresa true si la funcion en C responde de forma correcta o false en caso
    # contrario
    def self.incident_he_to_f
      dcel = ExampleDCEL.construct_example;

       f1 = Face.init_face("face 1",nil, nil)
       f2 = Face.init_face("face 2",nil, nil)
       f3 = Face.init_face("face 3",nil, nil)
       f4 = Face.init_face("face 4",nil, nil)
       f5 = Face.init_face("face 5",nil, nil)
       f6 = Face.init_face("face 6",nil, nil)
       f7 = Face.init_face("face 7",nil, nil)

       original_f1 = Face.cast_face(RBTree.rb_search(dcel[:face],f1))
       original_f2 = Face.cast_face(RBTree.rb_search(dcel[:face],f2))
       original_f3 = Face.cast_face(RBTree.rb_search(dcel[:face],f3))
       original_f4 = Face.cast_face(RBTree.rb_search(dcel[:face],f4))
       original_f5 = Face.cast_face(RBTree.rb_search(dcel[:face],f5))
       original_f6 = Face.cast_face(RBTree.rb_search(dcel[:face],f6))
       original_f7 = Face.cast_face(RBTree.rb_search(dcel[:face],f7))

       result_f1 = list_to_a(DCEL.incident_he_to_f(original_f1),"HALF_EDGE")
       result_f2 = list_to_a(DCEL.incident_he_to_f(original_f2),"HALF_EDGE")
       result_f3 = list_to_a(DCEL.incident_he_to_f(original_f3),"HALF_EDGE")
       result_f4 = list_to_a(DCEL.incident_he_to_f(original_f4),"HALF_EDGE")
       result_f5 = list_to_a(DCEL.incident_he_to_f(original_f5),"HALF_EDGE")
       result_f6 = list_to_a(DCEL.incident_he_to_f(original_f6),"HALF_EDGE")
       result_f7 = list_to_a(DCEL.incident_he_to_f(original_f7),"HALF_EDGE")

       return false if ["a","b","c","d"].sort{ |x,y| x<=>y } != result_f1
       return false if ["a'","b'","c'","d'","n","p","q","m","f","k","e","j"].sort{ |x,y| x<=>y } != result_f2
       return false if ["q'","p'","m'","n'"].sort{ |x,y| x<=>y } != result_f3
       return false if ["i'","j'","l'"].sort{ |x,y| x<=>y } != result_f4
       return false if ["l", "k'", "g"].sort{ |x,y| x<=>y } != result_f5
       return false if ["i", "e'", "h"].sort{ |x,y| x<=>y } != result_f6
       return false if ["h'", "f'", "g'"].sort{ |x,y| x<=>y } != result_f7
       
       return true
    end

  end
    
end
