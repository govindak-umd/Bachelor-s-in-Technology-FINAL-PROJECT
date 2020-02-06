% reference: Prof Kanan C, lecture notes, Automotive Chassis, VIT Vellore,
% Jan-June 2016.
% [IEEE Format for Reference writing - do web search]

%program to calculate turning circle radius
Wb=input('Enter Wheel Base: ');
Wt=input('Enter Wheel Track: ');
al=input('Enter inner wheel turn angle(in degrees): ');
al=pi*al/180;
bt=atan(Wb/(Wt+(Wb/tan(al))));

%calculating all dimensions
L=Wb/tan(al);
Tcr=(Wb/sin(bt))
hold on
grid off

%plotting the car
plot([0; Wt], [0; 0], 'LineWidth', 2,'color','b')
plot([0; 0], [0; Wb], 'LineWidth', 2,'color','b')
plot([0; Wt], [Wb; Wb], 'LineWidth', 2,'color','b')
plot([Wt; Wt], [0; Wb], 'LineWidth', 2,'color','b')

%setting the axises
xmin=(0-Wt/3);
xmax=1.1*(Wt+L);
ymin=(0-Wb/3);
ymax=Wb*1.3;
axis equal
axis([xmin xmax ymin ymax])
th=0.25*Wb/2;

%lotting rear wheels
plot([0; 0], [-th; th], 'LineWidth', 6,'color','r')
plot([Wt; Wt], [-th; th], 'LineWidth', 6,'color','r')

%plotting dotted lines
plot([Wt; Wt+L], [Wb; 0], 'LineWidth', 2,'color','k','LineStyle','--')
plot([Wt; Wt+L], [0; 0], 'LineWidth', 2,'color','k','LineStyle','--')

%plotting front wheels
plot([-th*sin(bt); th*sin(bt)], [Wb-th*cos(bt); Wb+th*cos(bt)], 'LineWidth', 6,'color','r')
plot([Wt-th*sin(al); Wt+th*sin(al)], [Wb-th*cos(al); Wb+th*cos(al)], 'LineWidth', 6,'color','r')

%plotting the legend
trg=plot([0; Wt+L], [Wb; 0], 'LineWidth', 2,'color','green','LineStyle','--');
lg=legend(trg,'Turning Circle Radius');
set(lg, 'Box', 'off')
set(lg, 'Color', 'none')
