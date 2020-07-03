# Thesis Simulation
Environment constants can be found in *src/global\_environment.h*.  

After executing the program, `.dat` files will be generated. You can use gnuplot to visualize them.\
To view AP and UE's location in room: 
```
gnuplot -p plot_room.gnu
```
To show AP and UE's association and location:
```
gnuplot -p plot_pair.gnu
```
To show all of above + AP's assigned RB \#:
```
gnuplot -p plot_fr.gnu
```

log files for 1st Tier Resource Allocation can be found under `./log/`

## TODO
- [x] Use channel formula
- [ ] NLOS channel
- [x] Resource block allocation (graph?!)
- [x] Output data for integration with NS-3
- [x] TDMA
- [x] Dynamic RA: 1st Tier
- [x] Remove candidate modulation schemes that does not fit requirement
- [ ] Dynamic RA: 2nd Tier
- [x] sort UE by channel (for NOMA)

## Note
- Angle(s) of irradiance and incidence:
   ![](https://www.researchgate.net/publication/311524364/figure/fig1/AS:567000930177024@1512194964905/Propagation-link-with-first-reflection-of-a-VLC-system.png)  
- On the issue of "order of Lambertian emission":  
   - [This paper](https://ieeexplore.ieee.org/abstract/document/1277847) says:  
when "semi-angle at half illuminance" = 60 deg, "order of Lambertian emission" = 1.
   - [This paper](https://www.researchgate.net/publication/337551362) gives different formula to calculate.
   - i am confusion. america exblain

> [time=Sun, Jun 28, 2020 03:07 AM]
