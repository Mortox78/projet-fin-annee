Sh include/Resources/Shader/BasicVertexShader.vs include/Resources/Shader/TextureFragmentShader.fs
Sh include/Resources/Shader/BasicVertexShader.vs include/Resources/Shader/ColorFragmentShader.fs
T ./resources/wall4_4.png 0
T ./resources/floor8-8.png 0
T ./resources/decoration/doors_leaf_closed.png 0



R { ---> 0

S 10 1 10

s 1 0 0/0/0 2/2


S 20 5 0.01
c 0 0 0/2/10 1/1/1
c 0 0 0/2/-10 1/1/1

S 0.01 5 20
c 0 0 10/2/0 1/1/1
c 0 0 -10/2/0 1/1/1

w [
e 0 4>./resources/Enemies/imp_run_anim_f0.png ./resources/Enemies/imp_run_anim_f1.png ./resources/Enemies/imp_run_anim_f2.png ./resources/Enemies/imp_run_anim_f3.png 0/10/0 0.5/0.5/0.5 9/9 10  
e 0 4>./resources/Enemies/big_demon_run_anim_f0.png ./resources/Enemies/big_demon_run_anim_f1.png ./resources/Enemies/big_demon_run_anim_f2.png ./resources/Enemies/big_demon_run_anim_f3.png 0/10/0 1/1/1 9/9 10
w ]

w [
e 0 4>./resources/Enemies/big_demon_run_anim_f0.png ./resources/Enemies/big_demon_run_anim_f1.png ./resources/Enemies/big_demon_run_anim_f2.png ./resources/Enemies/big_demon_run_anim_f3.png 0/10/0 1/1/1 20/20 1  
w ]

switch 2 0 0/1/10 2/3/0.5 0>1

E } ---> 0



R { --->1

S 1 1 1

s 1 0 0/0.001/15 5/10


S 1 3 0.01

c 0 0 0/2/10.001 5/1/1
c 0 0 0/2/19.999 5/1/1

S 0.01 5 10
c 0 0 2.5/1/15 1/1/1
c 0 0 -2.5/1/15 1/1/1


switch 2 0 0/1/10 2/3/0.5 1>0
switch 2 0 0/1/20 2/3/0.5 1>2

E }

R { ---> 2

S 10 1 10

s 1 0 0/0/40 2/4


S 20 5 0.01
c 0 0 0/2/20 1/1/1
c 0 0 0/2/60 1/1/1

S 0.01 5 20
c 0 0 10/2/40 1/1/2
c 0 0 -10/2/40 1/1/2


w [
e 0 4>./resources/Enemies/imp_run_anim_f0.png ./resources/Enemies/imp_run_anim_f1.png ./resources/Enemies/imp_run_anim_f2.png ./resources/Enemies/imp_run_anim_f3.png 0/10/40 0.5/0.5/0.5 20/20 10  
e 0 4>./resources/Enemies/big_demon_run_anim_f0.png ./resources/Enemies/big_demon_run_anim_f1.png ./resources/Enemies/big_demon_run_anim_f2.png ./resources/Enemies/big_demon_run_anim_f3.png 0/10/40 1/1/1 20/25 10
w ]

w [
e 0 4>./resources/Enemies/big_demon_run_anim_f0.png ./resources/Enemies/big_demon_run_anim_f1.png ./resources/Enemies/big_demon_run_anim_f2.png ./resources/Enemies/big_demon_run_anim_f3.png 0/10/40 1/1/1 20/20 1  
w ]

switch 2 0 0/1/20 2/3/0.5 2>1
switch 2 0 0/1/60 2/3/0.5 2>3

E } ---> 2


R { --->3

S 1 1 1

s 1 0 0/0.001/65 5/10

S 1 3 0.01

c 0 0 0/2/60.001 5/1/1
c 0 0 0/2/69.999 5/1/1

S 0.01 5 10
c 0 0 2.5/1/65 1/1/1
c 0 0 -2.5/1/65 1/1/1

switch 2 0 0/1/60 2/3/0.5 3>2
switch 2 0 0/1/70 2/3/0.5 3>4

E } ---> 3



R { ---> 4

S 10 1 10

s 1 0 0/0/90 4/4


S 20 5 1
c 0 0 0/2/70 2/1/1
c 0 0 0/2/110 2/1/1

S 0.001 5 40
c 0 0 20/2/90 2/1/2
c 0 0 -20/2/90 2/1/2


w [
e 0 4>./resources/Enemies/imp_run_anim_f0.png ./resources/Enemies/imp_run_anim_f1.png ./resources/Enemies/imp_run_anim_f2.png ./resources/Enemies/imp_run_anim_f3.png 0/10/90 0.5/0.5/0.5 9/9 10  
e 0 4>./resources/Enemies/big_demon_run_anim_f0.png ./resources/Enemies/big_demon_run_anim_f1.png ./resources/Enemies/big_demon_run_anim_f2.png ./resources/Enemies/big_demon_run_anim_f3.png 0/10/90 1/1/1 9/9 10
w ]

w [
e 0 4>./resources/Enemies/big_demon_run_anim_f0.png ./resources/Enemies/big_demon_run_anim_f1.png ./resources/Enemies/big_demon_run_anim_f2.png ./resources/Enemies/big_demon_run_anim_f3.png 0/10/90 1/1/1 20/20 1  
w ]

switch 2 0 0/1/70 2/3/1.5 4>3

E } ---> 4