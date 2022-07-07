%include "io.mac"
.DATA
file_name db "input.txt",0  ;name the file as input.txt
pro_child db 'Child Output:',0 ;output the string as child output:
pro_parent db 'Parent Output:',0 ;output the string as parent output:
.UDATA
     noof resd 1      ;no of elements we take as input
     fd resd 1        ;file descriptor
     num resd 1       ;value of input number
     count resd 1     ;auxiliary no of elements variable
     s_pointer resd 1 ;used to store pointer address 
     sum resd 1       ;store the sum of numbers
     array resd 1     ;stores starting array pointer after using mmap
.CODE
    .STARTUP
    ;using interrupt we create and open a file named as input.txt
    mov EAX,8
    mov EBX,file_name
    mov ECX,0q700
    int 0x80          
	
    mov [fd],EAX

    GetLInt [noof] ;getting input into noof variable
    mov EAX,[noof]
    mov [count],EAX ;same value into count variable
        
take_input:
    ;till count==0 we ask input for user
    GetLInt EAX
    mov [num],EAX
    ;using interrupt we write the input values into input.txt
    mov EAX,4 
    mov EBX,[fd] 
    mov ECX,num 
    mov EDX,4            
    int 0x80
    
    ;checking whether count==0 or not
    mov EDX,[count]
    dec EDX
    mov [count],EDX
    cmp EDX,0    
    je using_mmap ; if count==0 jump to mmap syscall
    jmp take_input 

using_mmap:

   ;using interrupt we will open the file input.txt
   mov EAX,5
   mov EBX,file_name
   mov ECX,2
   mov EDX,0q777
   int 0x80
    
   mov [fd],EAX
  ;implementing mmap on input.txt so that data converts into a array form
   mov  EAX,192
   mov  EBX,0 
   mov  ECX,4096  
   mov  EDX,0x2       
   mov  ESI,0x2            
   mov  EDI,[fd]
   mov  EBP,0                
   int  0x80                        
   
   mov [s_pointer],EAX

   mov EAX,2 ; implement fork syscall
   int 0x80
   cmp EAX,0 ;If the return value is 0, we are in the child process
   jz child
   
parent:
      call wait_for_child
      mov EAX,2
      mov EAX,[s_pointer]
      mov EDX,[noof]           
      mov [array],EAX        
      cmp EDX,1              
      jle print

      push EDX            
      push array
      call insertion_sort

;print the each element in new line in ascending order after completing insertion sort
print:                      
    mov ECX,EDX           
    mov EBX,EAX
    PutStr pro_parent
    nwln
    print_arr:                
        PutLInt [EBX]   
        nwln
        add EBX,4
        loop print_arr

	call exit_pro	
	

        
;wait till the child process is completed as fork syscall implement both the child and parent function simultaneously    
wait_for_child: 				
	         mov EAX,7
	         mov EBX,-1
	         mov ECX,0
	         mov EDX,0
	         int 0x80
	         ret

;function to perform insertion sort
insertion_sort:
            pushad
            mov EBP,ESP
            mov EBX,[EBP+36]
            mov ECX,[EBP+40]
            mov ESI,4

       forloop:
                mov EBX,[s_pointer]
                mov EDX,[EBX+ESI]
                mov EDI,ESI 
                sub EDI,4

        while_loop:
                cmp EDX,[EBX+EDI]
                jge exit_whi1e_loop
                mov EAX,[EBX+EDI]
                mov [EBX+EDI+4],EAX
                sub EDI,4 
                cmp EDI,0 
                jge while_loop

        exit_whi1e_loop:
                mov [EBX+EDI+4],EDX
                add ESI,4 
                dec ECX
                cmp ECX,1 
                jne forloop
                popad 
                ret 8
                
child:
    ;process used to add all numbers that are input by the user
    mov EAX,[noof]
    mov [count],EAX
    mov EAX,0
    mov [sum],EAX
    mov EBX,[s_pointer]
sum_numbers:
    mov EDX,[EBX]
    mov EAX,[sum]
    add EAX,EDX
    mov [sum],EAX
    add EBX,4
    mov EDX,[count]
    dec EDX
    mov [count],EDX
    cmp EDX,0
    je done_sum
    jmp sum_numbers

;print the sum of the numbers 
done_sum:
    PutStr pro_child
    mov EAX,[sum]
    nwln
    PutLInt EAX 
    nwln
    call exit_pro

;exit from the program
exit_pro:
        .EXIT

