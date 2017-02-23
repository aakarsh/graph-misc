(defstruct an/testcase name lines cmd  ans)
(defstruct an/testsuite name testcases dir)
(defvar an/testsuites '())

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
      (load-file f))))

(defun an/run-suite()
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


(defun an/run-test(test)
  (with-temp-buffer
    (mapcar
     (lambda(line)
       (insert (format "%s\n" line)))
     (an/testcase-lines test))
    (shell-command "make -k")
    (shell-command-on-region
     (point-min)
     (point-max)
     (format  "%s/bin/%s 2> %s" default-directory
              (an/testcase-cmd test)
              (format "%s/result-%s.log" default-directory (an/testcase-name test)))

     nil t)
    (buffer-string)))

(defun an/run-testsuite(ts)
  (let ((all-passed t)
        (default-directory (an/testsuite-dir ts)))
    (dolist (test (an/testsuite-testcases  ts))
      (let* ((ans (an/testcase-ans test))
             (result (an/run-test test))
            (name (an/testcase-name test)))
        (if (not (equal ans  result))
            (progn
              (message "Failed:%s->[%s] but was [%s]" name ans result)
              (setq all-passed  nil)))))
    (if all-passed
        (message "All tests passed !"))))
