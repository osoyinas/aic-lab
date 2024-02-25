// memory-mapped I/O addresses
# GPIO_SWs   = 0x80001400
# GPIO_LEDs  = 0x80001404
# GPIO_INOUT = 0x80001408

.equ delay, 1
# .equ delay, 10000000

.globl main


main:
  li t0, 0x80001400   # base address of GPIO memory-mapped registers
  li t1, 0xFFFF       # set direction of GPIOs
  sw t1, 8(t0)        # GPIO_INOUT = 0xFFFF
  li t1, 0x0001
  li t3, 15 	      # counter
  li t5, 0xFFFF       # mask of all leds on

repeat:

  mv t4, t3 # actual iteration counter

  loop_to_left:
	sw   t1, 4(t0)      # write value to LEDs: GPIO_LEDs = t1
	li t2, delay		# load delay counter
	delay_loop1:		# delay loop
		addi t2, t2, -1
	bnez t2, delay_loop1

	slli  t1, t1, 1	    # shift left 1 bit
  addi t4, t4, -1		# decrement counter
  bnez t4, loop_to_left # repeat loop

  mv t4, t3 # load actual iteration counter

  loop_to_right:
	sw   t1, 4(t0)       # write value to LEDs: GPIO_LEDs = t1
	li t2, delay
	
	delay_loop2:		 # delay loop
		addi t2, t2, -1
	bnez t2, delay_loop2

	srli t1, t1, 1		 # shift right 1 bit
    addi t4, t4, -1		 # decrement counter
  bnez t4, loop_to_right # repeat loop

  addi t3, t3, -1 # decrement counter to run less times
  slli t1, t1, 1  # shift left 0x0010
  addi t1, t1, 1  # add 1      0x0011

  bne t1, t5 , repeat # if t1 is not full, repeat
  li t1, 0x0001 # if it is full, reset t1
  li t3, 15 # reset counter


  j    repeat         # repeat loop
