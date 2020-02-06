% program to calculate turning circle radius for 2 wheel and 4 wheel steering
% reference: Prof Kanan C, lecture notes, Automotive Chassis, VIT Vellore, Jan-June 2016

clear all
clc

i=input('Enter (1) for 2 wheel steering, (2) for 4-wheel steering calculation: ');
if i==1
    clear all
    clc
    disp('       TWO WHEEL STEERING');
    Wb=273;         %Wheel Base
    Wt=250;        %Wheel track
    al=input('Enter front inner wheel turn angle(in degrees, less than 50°): ');
    if Wb<=0||Wt<=0||al<=0||al>50||imag(Wb)~=0||imag(Wt)~=0||imag(al)~=0
        disp('Error, please recheck values');
        return
    end
    al=pi*al/180;                           %front inner turn angle alpha
    bt=atan(Wb/(Wt+(Wb/tan(al))));  
    outer=(bt*180)/pi
    %front outer turn angle beta
    %calculating all dimensions
    L=Wb/tan(al);
    Tcr=(Wb/sin(bt));                       %Turning circle radius
    disp(['The turning circle radius is ',num2str(Tcr), ' units']);
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
    th=0.25*Wb/2;                           %tyre diameter, as a fraction of wheel base (aesthetics)
    %plotting rear wheels
    plot([0; 0], [-th; th], 'LineWidth', 5,'color','r')
    plot([Wt; Wt], [-th; th], 'LineWidth', 5,'color','r')
    %plotting dotted lines
    plot([Wt; Wt+L], [Wb; 0], 'LineWidth', 1,'color','k','LineStyle','--')
    plot([Wt; Wt+L], [0; 0], 'LineWidth', 1,'color','k','LineStyle','--')
    %plotting front wheels
    plot([-th*sin(bt); th*sin(bt)], [Wb-th*cos(bt); Wb+th*cos(bt)], 'LineWidth', 5,'color','r')
    plot([Wt-th*sin(al); Wt+th*sin(al)], [Wb-th*cos(al); Wb+th*cos(al)], 'LineWidth', 5,'color','r')
    %plotting the legend
    plot([0; Wt+L], [Wb; 0], 'LineWidth', 1,'color','green','LineStyle','--');
    text((Wt+L)/2,(Wb/2),['\leftarrow Tcr = ',num2str(Tcr), ' units'],'FontWeight','bold');
    
    hold off
    
elseif i==2
    
    % *program to calculate turning circle radius for 4 wheel drive*
    clear all
    clc
    disp('       FOUR WHEEL STEERING');
    %% taking inputs
    Wb=267;         %Wheel base
    Wt=173;        %Wheel track
    alf=input('Enter front inner wheel turn angle(in degrees, less than 50°): ');  
    if Wb<=0||Wt<=0||alf<=0||alf>50||imag(Wb)~=0||imag(Wt)~=0||imag(alf)~=0
        disp('Error, please recheck values');
        return
    end
    alf=pi*alf/180;                   %front inner turn angle alpha_front
    %% fitting curve to get rear turn angle vs front
    Fwa=[0, 10, 20, 25, 30, 35, 40, 45];
%     Rwa=[0, 4, 0, -9, -19, -27, -36, -45];
    Rwa=[0, 10, 20, 25, 30, 35, 40, 45];
    p=polyfit(Fwa,Rwa,4);
    %Fwa=0:1:45;
    %plot (Fwa,polyval(p,Fwa))
    alr=polyval(p,alf*180/pi);
    rearInner=alr
    alr=alr*pi/180;                       %rear inner turn angle alpha_rear
    %% plotting the car
    hold on
    grid off
    th=0.25*Wb/2;
    plot([0; Wt], [0; 0], 'LineWidth', 2,'color','b')
    plot([0; 0], [0; Wb], 'LineWidth', 2,'color','b')
    plot([0; Wt], [Wb; Wb], 'LineWidth', 2,'color','b')
    plot([Wt; Wt], [0; Wb], 'LineWidth', 2,'color','b')
    %% plotting front and rear inner tyres
    plot([Wt-th*sin(alf); Wt+th*sin(alf)], [Wb-th*cos(alf); Wb+th*cos(alf)], 'LineWidth', 5,'color','r')
    plot([Wt+th*sin(alr); Wt-th*sin(alr)], [th*cos(alr); -th*cos(alr)], 'LineWidth', 5,'color','r')
    %% finding turning radius point
    syms x y
    lri=(tan(-alr)*x)-(tan(-alr)*Wt)-y;     %line perpendicular to rear inner wheel
    lfi=-tan(alf)*x+Wb+Wt*tan(alf)-y;       %line perpendicular to front inner wheel
    P=solve(lri==0,lfi==0);                 %Point of intersection, turning circle center
    P.x=(double(P.x));
    P.y=(double(P.y));
    %% plotting lines from inner wheels
    plot([Wt; P.x], [0; P.y], 'LineWidth', 1,'color','k','LineStyle','--')
    plot([Wt; P.x], [Wb; P.y], 'LineWidth', 1,'color','k','LineStyle','--')
    %% finding outer wheel angles
    btr=-(atan(P.y/P.x));                   %rear outer turn angle beta_rear
    rearOuter=(btr*180)/pi
    btf=atan((Wb-P.y)/P.x);               %front outer turn angle beta_front
    frontOuter=(btf*180)/pi
    %% plotting outer wheels
    plot([th*sin(btr); -th*sin(btr)], [th*cos(btr); -th*cos(btr)], 'LineWidth', 5,'color','r')
    plot([-th*sin(btf); th*sin(btf)], [Wb-th*cos(btf); Wb+th*cos(btf)], 'LineWidth', 5,'color','r')
    %% plotting turning radius
    if pdist([0,0;P.x,P.y],'euclidean') >= pdist([0,Wb;P.x,P.y],'euclidean')    %checking which tyre is the farthest
        Tcr=pdist([0,0;P.x,P.y],'euclidean');
        plot([0; P.x], [0; P.y], 'LineWidth', 1,'color','green','LineStyle','--')
        plot([0; P.x], [Wb; P.y], 'LineWidth', 1,'color','k','LineStyle','--')
    else 
        Tcr=pdist([0,Wb;P.x,P.y],'euclidean');
        plot([0; P.x], [Wb; P.y], 'LineWidth', 1,'color','green','LineStyle','--')
        plot([0; P.x], [0; P.y], 'LineWidth', 1,'color','k','LineStyle','--')
     end
    disp(['The turning circle radius is ',num2str(Tcr), ' units']);
    %% Setting the graph
    xmin=(0-Wt/3);
    xmax=2*(Wt);
    ymin=(0-Wb/3);
    ymax=Wb*1.3;
    %axis([xmin xmax ymin ymax])
    axis image
    text(((P.x)/2),P.y+((Wb-P.y)/2),['\leftarrow Tcr = ',num2str(Tcr), ' units'],'FontWeight','bold')
    hold off
else
    clear all
    clc
    disp('Error, value incorrect, re-run program');
end