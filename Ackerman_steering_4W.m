
% *program to calculate turning circle radius for 4 wheel drive*
clear all
close all
clc

%% taking inputs
Wb=input('Enter Wheel Base: ');
Wt=input('Enter Wheel Track: ');
alf=input('Enter front inner wheel maximum turn angle(in degrees, less than 50°): ');
alf=pi*alf/180;

%% fitting curve to get rear turn angle vs front
Fwa=[0, 10, 20, 25, 30, 35, 40, 45];
Rwa=[0, 4, 0, -9, -19, -27, -36, -45];
p=polyfit(Fwa,Rwa,4);
%Fwa=0:1:45;
%plot (Fwa,polyval(p,Fwa))
alr=polyval(p,alf*180/pi);
alr=alr*pi/180;

%% plotting the car
hold on
grid off
th=0.25*Wb/2;
plot([0; Wt], [0; 0], 'LineWidth', 3,'color','b')
plot([0; 0], [0; Wb], 'LineWidth', 3,'color','b')
plot([0; Wt], [Wb; Wb], 'LineWidth', 3,'color','b')
plot([Wt; Wt], [0; Wb], 'LineWidth', 3,'color','b')

%% plotting front and rear inner tyres
plot([Wt-th*sin(alf); Wt+th*sin(alf)], [Wb-th*cos(alf); Wb+th*cos(alf)], 'LineWidth', 5,'color','r')
plot([Wt+th*sin(alr); Wt-th*sin(alr)], [th*cos(alr); -th*cos(alr)], 'LineWidth', 5,'color','r')

%% finding turning radius point
syms x y
lri=(tan(-alr)*x)-(tan(-alr)*Wt)-y;
lfi=-tan(alf)*x+Wb+Wt*tan(alf)-y;
P=solve(lri==0,lfi==0);
P.x=(double(P.x));
P.y=(double(P.y));

%% plotting lines from inner wheels
plot([Wt; P.x], [0; P.y], 'LineWidth', 1,'color','k','LineStyle','--')
plot([Wt; P.x], [Wb; P.y], 'LineWidth', 1,'color','k','LineStyle','--')

%% finding outer wheel angles
btr=-(atan(P.y/P.x));
btf=atan((Wb-P.y)/P.x);
btf*180/pi;

%% plotting outer wheels
plot([th*sin(btr); -th*sin(btr)], [th*cos(btr); -th*cos(btr)], 'LineWidth', 5,'color','r')
plot([-th*sin(btf); th*sin(btf)], [Wb-th*cos(btf); Wb+th*cos(btf)], 'LineWidth', 5,'color','r')
figure;
%% plotting turning radius
if pdist([0,0;P.x,P.y],'euclidean') >= pdist([0,Wb;P.x,P.y],'euclidean')
    Tcr=pdist([0,0;P.x,P.y],'euclidean')
    plot([0; P.x], [0; P.y], 'LineWidth', 1,'color','green','LineStyle','--')
    plot([0; P.x], [Wb; P.y], 'LineWidth', 1,'color','k','LineStyle','--')
else 
    Tcr=pdist([0,Wb;P.x,P.y],'euclidean')
    plot([0; P.x], [Wb; P.y], 'LineWidth', 1,'color','green','LineStyle','--')
    plot([0; P.x], [0; P.y], 'LineWidth', 1,'color','k','LineStyle','--')
end
    
%% Setting the graph
xmin=(0-Wt/3);
xmax=2*(Wt);
ymin=(0-Wb/3);
ymax=Wb*1.3;
%axis([xmin xmax ymin ymax])
axis image
hold off
