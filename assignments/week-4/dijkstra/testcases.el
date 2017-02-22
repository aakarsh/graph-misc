(setq an/testsuites
 (cons 
  (make-an/testsuite
   :name "dijkstra"
   :dir "/home/aakarsh/src/c++/graphs/assignments/week-4/dijkstra"
   :testcases
  (list
   (make-an/testcase  
    :name "simple-1"
    :lines '(
             "4 4"
             "1 2 1"
             "4 1 2"
             "2 3 2"
             "1 3 5"
             "1 3")
    :cmd "dijkstra"
    :ans "3")

   (make-an/testcase  
    :name "simple-2"
    :lines '(
             "4 4"
             "1 2 1"
             "4 1 2"
             "2 3 2"
             "1 3 5"
             "3 1")
    :cmd "dijkstra"
    :ans "-1")))
  an/testsuites))

