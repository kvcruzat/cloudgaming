from mininet.topo import Topo
from mininet.link import TCLink

class CloudTopo( Topo ):
    "Simple cloud gaming topology"

    def __init__( self ):
        "Create custom cloud topo."

        # Initialize topology
        Topo.__init__( self )

        # Add hosts and switches
        playerHost1 = self.addHost( 'h1' )
        playerHost2 = self.addHost( 'h2' )
        playerHost3 = self.addHost( 'h3' )
        coreSwitch = self.addSwitch( 's1' )
        aggSwitch1 = self.addSwitch( 's2' )
        aggSwitch2 = self.addSwitch( 's3' )
        torSwitch1 = self.addSwitch( 's4' )
    	torSwitch2 = self.addSwitch( 's5' )
    	torSwitch3 = self.addSwitch( 's6' )
    	torSwitch4 = self.addSwitch( 's7' )
        cloudHost1 = self.addHost( 'h4' )
        cloudHost2 = self.addHost( 'h5' )
        cloudHost3 = self.addHost( 'h6' )
    	cloudHost4 = self.addHost( 'h7' )
        cloudHost5 = self.addHost( 'h8' )
        cloudHost6 = self.addHost( 'h9' )
    	cloudHost7 = self.addHost( 'h10' )
        cloudHost8 = self.addHost( 'h11' )

        # self.addLink( playerHost1, coreSwitch)
        # self.addLink( playerHost2, coreSwitch)
        # self.addLink( playerHost3, coreSwitch)
        # self.addLink( coreSwitch, aggSwitch1)
        # self.addLink( coreSwitch, aggSwitch2)

        # self.addLink( aggSwitch1, torSwitch1)
        # self.addLink( aggSwitch1, torSwitch2)
        # self.addLink( aggSwitch1, torSwitch3)
        # self.addLink( aggSwitch1, torSwitch4)
        # self.addLink( aggSwitch2, torSwitch1)
        # self.addLink( aggSwitch2, torSwitch2)
        # self.addLink( aggSwitch2, torSwitch3)
        # self.addLink( aggSwitch2, torSwitch4)

        # self.addLink( torSwitch1, cloudHost1)
        # self.addLink( torSwitch1, cloudHost2)
        # self.addLink( torSwitch2, cloudHost3)
        # self.addLink( torSwitch2, cloudHost4)
        # self.addLink( torSwitch3, cloudHost5)
        # self.addLink( torSwitch3, cloudHost6)
        # self.addLink( torSwitch4, cloudHost7)
        # self.addLink( torSwitch4, cloudHost8)
        
        self.addLink( playerHost1, coreSwitch,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( playerHost2, coreSwitch,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( playerHost3, coreSwitch,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( coreSwitch, aggSwitch1,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( coreSwitch, aggSwitch2,
        				bw=10, delay='15ms', loss=0, max_queue_size=1000, use_htb=True )

        self.addLink( aggSwitch1, torSwitch1,
        				bw=10, delay='20ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( aggSwitch1, torSwitch2,
            				bw=10, delay='20ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( aggSwitch1, torSwitch3,
            				bw=10, delay='20ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( aggSwitch1, torSwitch4,
            				bw=10, delay='20ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( aggSwitch2, torSwitch1,
            				bw=10, delay='20ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( aggSwitch2, torSwitch2,
            				bw=10, delay='20ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( aggSwitch2, torSwitch3,
            				bw=10, delay='20ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( aggSwitch2, torSwitch4,
            				bw=10, delay='20ms', loss=0, max_queue_size=1000, use_htb=True )

        self.addLink( torSwitch1, cloudHost1,
            				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( torSwitch1, cloudHost2,
            				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( torSwitch2, cloudHost3,
            				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( torSwitch2, cloudHost4,
            				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( torSwitch3, cloudHost5,
            				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( torSwitch3, cloudHost6,
            				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( torSwitch4, cloudHost7,
            				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
    	self.addLink( torSwitch4, cloudHost8,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )

topos = { 'cloudtopo': ( lambda: CloudTopo() ) }
