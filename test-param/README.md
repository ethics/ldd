# test

A simple test module with parameter, passing arguments to module

## Commands to manage the module

- Following the kernel's log for new lines
  ~~~
  sudo dmesg -W
  ~~~
- Inserting the module:
  ~~~
  sudo insmod test-param.ko debug=1
  ~~~
- Removing the module:
  ~~~
  sudo rmmod test-param
  ~~~
- Viewing the module parameter value passed
  ~~~
  sudo cat /sys/module/test_param/parameters/debug
  ~~~

