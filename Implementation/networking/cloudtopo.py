from mininet.topo import Topo
from mininet.link import TCLink

# Previous network topology

class CloudTopo( Topo ):
    "Simple cloud gaming topology"

    def __init__( self ):
        "Create custom cloud topo."

        # Initialize topology
        Topo.__init__( self )

        # Add hosts and switches
        cloudHost = self.addHost( 'ch' )
        playerHost1 = self.addHost( 'h1' )
        playerHost2 = self.addHost( 'h2' )
        playerHost3 = self.addHost( 'h3' )
        cloudSwitch = self.addSwitch( 's1' )
        leftSwitch = self.addSwitch( 's2' )
        middleSwitch = self.addSwitch( 's3' )
        rightSwitch = self.addSwitch( 's4' )
        exitSwitch = self.addSwitch( 's5' )

        # Add links
        self.addLink( cloudHost, cloudSwitch )
        # self.addLink( cloudSwitch, leftSwitch )
        # self.addLink( cloudSwitch, middleSwitch )
        # self.addLink( cloudSwitch, rightSwitch )
        # self.addLink( leftSwitch, exitSwitch )
        # self.addLink( middleSwitch, exitSwitch )
        # self.addLink( rightSwitch, exitSwitch )

        # self.addLink( playerHost1, exitSwitch)
        # self.addLink( playerHost2, exitSwitch)
        # self.addLink( playerHost3, exitSwitch)
        
        self.addLink( playerHost1, exitSwitch,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( playerHost2, exitSwitch,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( playerHost3, exitSwitch,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( exitSwitch, leftSwitch,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( exitSwitch, middleSwitch,
        				bw=10, delay='15ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( exitSwitch, rightSwitch,
        				bw=10, delay='20ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( leftSwitch, cloudSwitch,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( middleSwitch, cloudSwitch,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )
        self.addLink( rightSwitch, cloudSwitch,
        				bw=10, delay='10ms', loss=0, max_queue_size=1000, use_htb=True )



topos = { 'cloudtopo': ( lambda: CloudTopo() ) }