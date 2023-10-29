simple server
{
    @display("i=block/source;p=230,40");
    gates:
        input radioIn @directIn;
}

//
// TODO documentation
//
simple client
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;

}

simple client2
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client3
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client4
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client5
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client6
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client7
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client8
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client9
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client10
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client12
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client13
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client14
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client15
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client16
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client17
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client18
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client19
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client20
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client21
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client22
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client23
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client24
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client25
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client26
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client27
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client28
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client29
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

simple client30
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}
simple utilitycenter
{
    @display("i=block/source;p=230,40");
    gates:
        input radioIn @directIn;
}



simple client11
{
    @display("i=block/sink;p=230,40");
    gates:
        input radioIn @directIn;
}

//
// TODO documentation
//
network Network
{
    @display("bgb=8000,8000");


    submodules:

        DataConcentrator: server {
            @display("p=4009.0051,1146.145");
        }
        SmartMeter1: client {
            @display("p=2577.5752,200.20001");
        }
        SmartMeter2: client2 {


            @display("p=2282.28,2267.2651");
        }

        SmartMeter3: client3 {


            @display("p=4009.0051,3333.33");
        }

        SmartMeter4: client4 {


            @display("p=5980.975,2592.59");
        }

        SmartMeter5: client5 {


            @display("p=5480.475,330.33002");
        }

        SmartMeter6: client6 {


            @display("p=1711.7101,135.13501");
        }

        SmartMeter7: client7 {


            @display("p=1256.255,500.50003");
        }

        SmartMeter8: client8 {


            @display("p=1451.4501,1341.3401");
        }

        SmartMeter9: client9 {


            @display("p=2087.085,1451.4501");
        }

        SmartMeter10: client10 {


            @display("p=990.99005,1071.0701");
        }

        SmartMeter11: client11 {


            @display("p=1301.3,2267.2651");
        }

        SmartMeter12: client12 {


            @display("p=910.91003,2672.6702");
        }

        SmartMeter13: client13 {


            @display("p=990.99005,3068.0652");
        }

        SmartMeter14: client14 {


            @display("p=1531.53,3333.33");
        }

        SmartMeter15: client15 {


            @display("p=2222.22,3068.0652");
        }

        SmartMeter16: client16 {


            @display("p=3098.0952,3868.8652");
        }

        SmartMeter17: client17 {


            @display("p=3293.29,4379.375");
        }

        SmartMeter18: client18 {


            @display("p=3888.885,4574.5703");
        }

        SmartMeter19: client19 {


            @display("p=4469.4653,4454.45");
        }

        SmartMeter20: client20 {


            @display("p=4589.585,3908.905");
        }

        SmartMeter21: client21 {


            @display("p=5650.645,3208.205");
        }

        SmartMeter22: client22 {


            @display("p=6176.1704,3558.5552");
        }

        SmartMeter23: client23 {


            @display("p=6706.7,3278.2751");
        }

        SmartMeter24: client24 {


            @display("p=6831.825,2912.9102");
        }

        SmartMeter25: client25 {


            @display("p=6706.7,2537.5352");
        }

        SmartMeter26: client26 {


            @display("p=6246.24,1211.2101");
        }

        SmartMeter27: client27 {


            @display("p=6901.895,950.95");
        }

        SmartMeter28: client28 {


            @display("p=7192.185,695.695");
        }

        SmartMeter29: client29 {


            @display("p=6996.99,425.42502");
        }

        SmartMeter30: client30 {


            @display("p=6441.435,105.105");
        }


        UtilityCenter: utilitycenter {
            @display("p=4009.0051,555.555");

        }
}

