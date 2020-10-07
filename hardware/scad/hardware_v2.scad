LARGEUR = 60;
LONGUEUR = 100;


// Roue 

translate ([24,27,32]) {
    difference() {
        rotate([90]) import("Bead_Chain_Pulley_-_More_Versatile.stl"); 
        translate ([0,0,-10]) {
             difference() {
                color("green");
                cylinder (h=30, r=3, $fn=100);
                translate ([-12,-5,0]) {
                    color("red") cube([10,10,100]);
                }
             }
        }
    }
}

// Plateau
difference() {
    color("red");
    cube([LARGEUR,LONGUEUR,3]);
	translate ([6,6,-0.1]) {
	    cylinder (h = 4.1, r= 2, $fn=100);
	}
    translate ([LARGEUR-6,6,-0.1]) {
	    cylinder (h = 4.1, r= 2, $fn=100);
	}
    translate ([6,LONGUEUR-6,-0.1]) {
	    cylinder (h = 4.1, r= 2, $fn=100);
	}
    translate ([LARGEUR-6,LONGUEUR-6,-0.1]) {
	    cylinder (h = 4.1, r= 2, $fn=100);
	}
}

// Bloc Moteur

translate ([6,10,3]) {
    color("red")
    difference() {
        cube([36,80,25]);
        translate ([2,2,0.1]) {
            cube([32,46,26]);
        }
        translate ([4,46,0.1]) {
            cube([26,40,26]);
        }
    }
}

// Goutiere moteur

translate ([6,0,28]) { // 6,0,28
    color("orange")
    difference() {
        cube([36,58,12]);
        translate ([2,-10,3]) {
            cube([32,40,26]);
        }
        translate ([18,30,3]) {
            cylinder (h = 15, r= 16, $fn=100);
        }
        // trou axe moteur
        translate ([18,27,-1]) {
            cylinder (h = 15, r= 3.5, $fn=100);
        }
        // trou fixation 1
        translate ([27,52,-1]) {
            cylinder (h = 15, r= 2, $fn=100);
        }
        // trou fixation 2
        translate ([9,52,-1]) {
            cylinder (h = 15, r= 2, $fn=100);
        }
        translate ([-10,48,3]) {
            cube([50,40,26]);
        }
    }
}

// Couvercle

translate ([80,-3,0]) { //-3,-3,0
    difference() {
        color("yellow")
        cube([LARGEUR+6,LONGUEUR+6,50]);
        translate ([3,3,-0.1]) {
            cube([LARGEUR,LONGUEUR,47.1]);
        }
        //sortie chaine
        translate ([11,-20,31]) {
            color("blue");
            cube([32,58,11]);
        }
        //photoresistance
        translate ([52,-20,37.8]) {
            color("blue");
            cube([5,58,4.2]);
        }
        //dht22
        translate ([48,-20,10]) {
            color("blue");
            cube([15,58,20]);
        }
        //alimentation
        translate ([48,-20,10]) {
            color("blue");
            cube([10,500,8]);
        }
    }
    translate([LARGEUR-9,20,4]){
        difference() {
            cube([12,12,5]);
            translate([6,6,0]){
                cylinder (h = 1, r= 5, $fn=100);
            }
        }
    }
    
    translate([LARGEUR-9,LONGUEUR-20,4]){
        difference() {
            cube([12,12,5]);
            translate([6,6,0]){
                cylinder (h = 1, r= 5, $fn=100);
            }
        }
    }
}

