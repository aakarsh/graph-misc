(defun an/random-graph-lines(nvertices nedges)
  (let ((n (- nvertices 1))
        (result '()))  
    (dotimes (k nedges result)
      (setq result (cons 
                    (format "%s %s %s"
                            (+ 1 (random n)) (+ 1 (random n))
                            (if (mod n 2)(* -1 (+ 1 (random n))) (+ 1 (random n))))
                    result)))
      result))

(defun an/find-negative-graph(nvertices nedges niter)
  (interactive "nEnter Number Vertices:\nnEnter Number Edges:\nnNumber Iterations:")
  (if (catch 'foo
    (dotimes (n 100)
      (let((lines (an/random-graph-lines nvertices nedges)))
        (if (equal "0" (an/run-test
                        (make-an/testcase
                         :name "randome"
                         :lines (cons (format "%d %d" nvertices nedges) lines)
                         :cmd "negative_cycle"
                         :ans "0")))
            (progn 
              (message "Found negative graph: ")
              (message "%d %d" nvertices nedges)
              (dolist (line lines)
                (message "%s" line))
              (throw 'foo t))))))
      (message  "done.")))
    

(setq an/testsuites
 (cons
  (make-an/testsuite
   :name "negative_cycle"
   :dir "/home/aakarsh/src/c++/graphs/assignments/week-4/negative_cycle"
   :testcases
  (list

   (make-an/testcase
    :name "one-negative-cycle"
    :lines '(
             "4 4"
             "1 2 -5"
             "4 1 2"
             "2 3 2"
             "3 1 1")
    :cmd "./negative_cycle"
    :ans "1")

   (make-an/testcase
    :name "disconnected-graph"
    :lines '(
             "5 4"
             "1 2 1"
             "3 4 -1"
             "4 5 -1"
             "5 3 1")
    :cmd "./negative_cycle"
    :ans "1")

   (make-an/testcase
    :name "non-negative-cycle-disconnected-graph-2"
    :lines '(
             "5 4"
             "1 2 1"
             "3 4 1"
             "4 5 1"
             "5 3 1")
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase
    :name "non-negative-cycle-disconnected-graph-3"
    :lines '(
             "5 4"
             "1 2 1"
             "3 4 -1"
             "4 5 1"
             "5 3 1")
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase
    :name "non-negative-cycle-disconnected-graph-4"
    :lines '(
             "5 4"
             "1 2 -1"
             "3 4 -1"
             "4 5 1"
             "5 3 1")
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase
    :name "non-negative-cycle-5"
    :lines '(
             "4 5"
             "1 2 1"
             "2 3 1"
             "3 4 1"
             "4 1 1"
             "2 4 -1")
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase
    :name "non-negative-cycle-6"
    :lines '(
             "2 2"
             "1 2 -1"
             "2 1 1"
             )
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase
    :name "negative-cycle-7"
    :lines '(
             "2 2"
             "1 2 -1"
             "2 1 -1"
             )
    :cmd "./negative_cycle"
    :ans "1")

   (make-an/testcase
    :name "negative-cycle-7"
    :lines '(
             "4 4"
             "1 2 1"
             "2 1 -1"
             "3 4 -2"
             "4 3 1"
             )
    :cmd "./negative_cycle"
    :ans "1")

   (make-an/testcase
    :name "no-edges-1"
    :lines '(
             "10 0"
             )
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase
    :name "no-no-cycle-negative-acycliec"
    :lines '(
             "5 4"
             "1 2 -1"
             "4 2 -1"
             "3 2 -1"
             "4 5 -1"
             )
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase
    :name "single-vertex-self-loop"
    :lines '(
             "10 1"
             "5 5 -1"
             )
    :cmd "./negative_cycle"
    :ans "1")   
  
   (make-an/testcase
    :name "single-vertex-self-loop"
    :lines '(
             "10 10"
             "6 9 -3"
             "2 1 -2"
             "3 8 -3"
             "7 3 -1"
             "8 5 -5"
             "3 8 -5"
             "7 9 -2"
             "6 9 -8"
             "7 5 -5"
             "5 6 -4")
    
    :cmd "./negative_cycle"
    :ans "0")

))
  
  ;; (make-an/testcase
  ;;  :name "random-graph"
  ;;  :lines (an/random-graph-lines 10 10)
  ;;  :cmd "./negative_cycle"
  ;;  :ans "1")
  
  an/testsuites))