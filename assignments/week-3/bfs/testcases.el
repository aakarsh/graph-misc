(setq an/testsuites
 (cons 
  (make-an/testsuite
   :name "bfs"
   :dir "/home/aakarsh/src/c++/graphs/assignments/week-3/bfs"
   :testcases
  (list
   (make-an/testcase  
    :name "simple-1"
    :lines '(
             "4 4"
             "1 2"
             "4 1"
             "2 3"
             "3 1"
             "2 4")    
    :cmd "bfs"
    :ans "2")

   (make-an/testcase  
    :name "simple-2"
    :lines '(
             "5 4"
             "5 2"
             "1 3"
             "3 4"
             "1 4"
             "3 5")    
    :cmd "bfs"
    :ans "-1")))
  an/testsuites))

