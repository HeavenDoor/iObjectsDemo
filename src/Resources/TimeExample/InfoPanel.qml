import QtQuick 2.4
Item{
	function onTopBtnClicked(index){
		console.log(index)
		switch(index)
		{
			case 0:
				sBtn.setSource("s.png");
				eBtn.setSource("e.png");
			break;
			case 1:
				sBtn.setSource("s.png");
				tBtn.setSource("t.png");
				break;
			case 2:
				eBtn.setSource("e.png");
				tBtn.setSource("t.png");
				break;
			default: break;
		}
	}
	function collesBtnClicked(){
		
	}

	Rectangle {
		id: widget
		color: "#00000000"
		width: 270; height: 380
	
		BorderImage {
			width: 270; height: 380
			border { left: 20; top: 65; right: 20; bottom: 20 }
			horizontalTileMode: BorderImage.Stretch
			verticalTileMode: BorderImage.Stretch
			source: "ccv.png"
		}
	
	
		Rectangle {
			color: "#00000000"
			width: 180; height: 40
			x: 20
			y: 8
			Button {
				id: tBtn
				x: 5
				y:3
				z: 3
				imgWidth : 32
				imgHeight: 32
				pressImg: "tp.png"
				normalImg: "t.png"
				sourceImg: "tp.png"
				onButtonClicked: onTopBtnClicked(0)
				
			}

			Button {
				id: eBtn
				x: tBtn.x + tBtn.imgWidth + 10
				y:3
				z: 3
				imgWidth : 32
				imgHeight: 32
				pressImg: "ep.png"
				normalImg: "e.png"
				sourceImg: "e.png"
				onButtonClicked: onTopBtnClicked(1)
			}

			Button {
				id: sBtn
				x:  eBtn.x + eBtn.imgWidth + 10
				y:3
				z: 3
				imgWidth : 32
				imgHeight: 32
				pressImg: "sp.png"
				normalImg: "s.png"
				sourceImg: "s.png"
				onButtonClicked: onTopBtnClicked(2)
			}

			Button {
				id: collesBtn
				x: widget.width - 65
				y: 5
				z: 3
				imgWidth : 25
				imgHeight: 26
				pressImg: "colles.png"
				normalImg: "colles.png"
				sourceImg: "colles.png"
				onButtonClicked: collesBtnClicked()
			}			
		}
	}
}


