# Thesis Simulation
Environment constants can be found in *src/global\_environment.h*.  
Structure:  
```
- main.cpp
+ /src
  |- global_environment.h  
  |- channel.cc  
  |- channel.h  
  |- clustering.cc  
  |- clustering.h  
  |- node.cc  
  |- node.h  
```

After executing the program, 3 `.dat` files will be generated. \
To view AP and UE's location in room, run `gnuplot -p plot_room.gnu`. \
Use `gnuplot -p plot_pair.gnu` instead to show AP and UE's relationship as well.

## TODO
- [x] Use channel formula
- [ ] Resource block allocation (graph?!)

## Note
- Angle(s) of irradiance and incidence:
   ![](https://www.researchgate.net/publication/311524364/figure/fig1/AS:567000930177024@1512194964905/Propagation-link-with-first-reflection-of-a-VLC-system.png)  
- On the issue of "order of Lambertian emission":  
   - [This paper](https://ieeexplore.ieee.org/abstract/document/1277847) says:  
when "semi-angle at half illuminance" = 60 deg, "order of Lambertian emission" = 1.
   - [This paper](https://www.researchgate.net/publication/337551362) gives different formula to calculate.
   - i am confusion. america exblain

> [time=Sat, May 30, 2020 04:08 AM]
