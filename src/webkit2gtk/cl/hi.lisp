(ql:quickload :cl-cffi-gtk)

(asdf:load-system :cl-cffi-gtk)

(defpackage :gtk-tutorial
  (:use :gtk :gdk :gdk-pixbuf :gobject
   :glib :gio :pango :cairo :common-lisp))

(in-package :gtk-tutorial)

(defun raw-simple-window ()
  (within-main-loop
    (let (;; create a toplevel window.
          (window (gtk-window-new :toplevel)))
      ;; signal handler for the window to handle the signal "destroy".
      (g-signal-connect window "destroy"
                        (lambda (widget)
                          (declare (ignore widget))
                          (leave-gtk-main)))
			(gtk-window-title )
      ;; show the window.
      (gtk-widget-show-all window))))


(defun raw-simple-window1 ()
  (within-main-loop
    (let (;; create a toplevel window.
          (window (make-instance 'gtk-window
																 :type :toplevel
																 :title "B"
																 :default-width 800)))
      ;; signal handler for the window to handle the signal "destroy".
      (g-signal-connect window "destroy"
                        (lambda (widget)
                          (declare (ignore widget))
                          (leave-gtk-main)))
      ;; show the window.
      (gtk-widget-show-all window))))
