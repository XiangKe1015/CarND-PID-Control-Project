# CarND-PID-Control-Project
Udacity Term2 P4 Self Driving Car PID control Project


###  Describe the effect each of the P, I, D components had in your implementation.
P is the propotional of cte (bias from centerline) as a control feedback current state, that is in next step, will correct current cte with some propotion.

But if only with I controller, the oscillates will happens, and normally when larger p was chosen, the oscillates faster.
D controller will help to aviod the overshoot, D*((CTE_t - CTE_t_1) / delta_t), means the controller will noticed when the car has turned enough to reduce the  cte and won't go shooting for the centerline. The error is becoming smaller over time, it conter steers, it steer up again. This will allow the car to gracefully approach the target trajectory.

But normally a "systematic bias" ocurrs in robotics, if the car system steer a liggle bit stronger, only with PD controller, need to sustained situation with a large error. This is measured by the the sum of the cte over time, I controller will take a propotion to the sum of cte, which will eventually correct the robot's motion.

###  Describe how the final hyperparameters were chosen.
I start with the params used in previous lesson, P = 0.2, D = 3.0, I = 0.004.
And it proved the car can drive whole cycle successful with these params. Then, I twiddle the params, with the algorithm showed in previous lesson, for each small twiddle cycle, take 1st 1600 to adjust car postion, make it stable(normally we do need so much steps for adjust car postion, 100 is enough), take 2nd 1600 step(like 1 whole cycle) to calculate the total cte, to evaluate the params choosed. I runed 1000 cycles, The params changed a bit in the process, like D changed to 3,3, 3.5, I change to 0.0048, I changed to 0.21, 0.187, but seems quite hard to coverged, and normally it will change back to P = 0.2, D = 3.0, I = 0.004. So I finnaly used this group of params.


