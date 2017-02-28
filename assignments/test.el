(defstruct an/testcase name lines cmd  ans)
(defstruct an/testsuite name testcases dir)

(defvar an/testsuites '())

(require 'cl)
(require 'find-lisp)

(defun an/pwd()
  (let ((pwd (shell-command-to-string "pwd")))
    (substring pwd 0 (- (length pwd) 1))))

(defun string-ltrim (str)
  (let ((trim-pos (string-match "\\s +$" str)))
    (if trim-pos
        (substring str 0 trim-pos)
      str)))

(defun string-rtrim (str)
  (let ((trim-pos (string-match "[^ \t\n\r]+" str)))
    (if trim-pos
        (substring str trim-pos)
      str)))

(defun string-trim (str)
  (string-rtrim (string-ltrim str)))

(defun an/load-suites()
  (let ((testcase-files (find-lisp-find-files default-directory ".*testcases.el$")))
    (setq an/testsuites nil)
    (dolist (f testcase-files)
      ;; TODO  : Need the capture the current working directory here 
      (load-file f))))

(defun an/run-all-testsuites()
  (interactive)
  (an/load-suites)
  (dolist (ts an/testsuites)
    (an/run-testsuite ts)))
  
(defun an/run-testsuites()
  (interactive)
  (an/load-suites)
  (let ((found-suite nil )
        (name    (ido-completing-read "Testsuite Name:" (mapcar 'an/testsuite-name an/testsuites))))
  (dolist(ts an/testsuites)
    (if (and (an/testsuite-p ts)
             (equal (string-trim name) (an/testsuite-name ts)))
        (progn
          (setq found-suite t)
          (an/run-testsuite ts))))
  (if (not found-suite)
      (message "No testsuite [%s] found " name))))

;; convenience
(global-set-key "\C-ct" 'an/run-testsuites)

(defun an/lines-to-string(lines)
  (setq lines  (mapcar (lambda(l) (format "%s \n" l) ) lines))
  (let ((retval ""))
    (dolist (line lines)
      (setq retval (concat  retval line)))
    retval))

(defun an/run-test(dir test)
  (let ((log-file (format "%s/result-%s.log" dir (an/testcase-name test)))
        (cmd (an/testcase-cmd test))
        (lines (an/testcase-lines test)))
  (with-temp-buffer
    (insert (an/lines-to-string lines))    
;;    (shell-command (format "$(cd %s; make -k)" dir))
    (shell-command-on-region (point-min)  (point-max)
     (format  "%s/bin/%s 2> %s" dir (an/testcase-cmd test)
              log-file)
     nil t)
    (buffer-string))))
  
(defun an/run-testsuite(ts)
  (let ((all-passed t)
        (num-failures 0)
        (default-directory (an/testsuite-dir ts)))
    (with-current-buffer (get-buffer-create (format "*test-results:[%s]*" (an/testsuite-name ts)))
      (pop-to-buffer (current-buffer))
      (delete-region (point-min) (point-max))
      (insert "+----------+--------------------------------------------------------------+\n")      
      (insert (format "|%-10s|%-40s|%-10s|%-10s|\n" "Result" "Name" "Expected" "Result"))
      (insert "+----------+--------------------------------------------------------------+\n")      
    (dolist (test (an/testsuite-testcases  ts))
      (let* ((ans (an/testcase-ans test))
             (result (an/run-test (an/testsuite-dir ts) test))
            (name (an/testcase-name test)))        

        (if (not (equal ans  (string-trim result)))
            (progn
              (insert (foramt "|%-10s" "*FAIL* "))
              (message "Failed:%s->[%s] but was [%s]" name ans result)
              (incf num-failures)
              (setq all-passed  nil))
          (insert (format "|%-10s" "*PASS* ")))        
        (insert (format "|%-40s|%-10s|%-10s|\n" name ans result))))
    (if all-passed
        (progn
          (insert "+----------+--------------------------------------------------------------+\n")      
                
          (insert "*ALL TESTS PASSED!*\n")
          (message "All tests passed !"))
      (message "*FAILED %d Tests !!" num-failures)
      (insert (format "*FAILED* %d Tests !!" num-failures))))))


;; (defun an/dired-copy-to-other-dired()
;;   (interactive)
;;   (let ((file (dired-get-file-for-visit)))    
;;     (with-current-buffer (get-buffer (other-buffer))      
;;       (dired-copy-file file (dired-current-directory) nil))))q

