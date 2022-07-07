Sh include/Resources/Shader/BasicVertexShader.vs include/Resources/Shader/TextureFragmentShader.fs
Sh include/Resources/Shader/BasicVertexShader.vs include/Resources/Shader/ColorFragmentShader.fs
T ./resources/wall4_4.png 0
T ./resources/floor8-8.png 0
T ./resources/decoration/doors_leaf_closed.png 0


R { ---> 4

S 40 0.1 40

s 1 0 0/0/0 1/1


S 20 5 1
c 0 0 0/2/-20 2/1/1
c 0 0 0/2/20 2/1/1

S 01 5 40
c 0 0 20/2/0 2/1/2
c 0 0 -20/2/0 2/1/2


w [
e 0 4>./resources/Enemies/imp_run_anim_f0.png ./resources/Enemies/imp_run_anim_f1.png ./resources/Enemies/imp_run_anim_f2.png ./resources/Enemies/imp_run_anim_f3.png 0/10/0 0.5/0.5/0.5 9/9 10  
e 0 4>./resources/Enemies/big_demon_run_anim_f0.png ./resources/Enemies/big_demon_run_anim_f1.png ./resources/Enemies/big_demon_run_anim_f2.png ./resources/Enemies/big_demon_run_anim_f3.png 0/10/0 1/1/1 9/9 10
w ]

w [
e 0 4>./resources/Enemies/big_demon_run_anim_f0.png ./resources/Enemies/big_demon_run_anim_f1.png ./resources/Enemies/big_demon_run_anim_f2.png ./resources/Enemies/big_demon_run_anim_f3.png 0/10/0 1/1/1 20/20 1  
w ]

dswitch 2 0 0/1/20 2/3/0.5 2>1
switch 2 0 0/1/70 2/3/0.5 4>3

E } ---> 4
