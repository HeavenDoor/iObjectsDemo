import QtQuick 2.4

Item{
	function onTopBtnClicked(index){
		console.log(index)
		switch(index)
		{
			case 0:
				sBtn.setSource("qrc:/s.png");
				eBtn.setSource("qrc:/ef.png");
				{
					textArea.height = text1.x + text1.height + textArea.vSpace + text2.height  + textArea.vSpace + text3.height + textArea.vSpace
					text4.text = "所有的动画元素都是从Animation元素继承的 这些方法控制了动画的执行";
					animationText.start();
				}
			break;
			case 1:
				sBtn.setSource("qrc:/s.png");
				tBtn.setSource("qrc:/t.png");
				break;
			case 2:
				eBtn.setSource("qrc:/ef.png");
				tBtn.setSource("qrc:/t.png");
				break;
			default: break;
		}
	}
	function collesBtnClicked(){
		expandBtn.visible = false
		animWidthDecrease.start();
		
	}
	function expandBtnClicked(){
		expandBtn.visible = false
		animWidthIncrease.start();
		
	}

	function animationIncreaseFinished(){
		console.log("Increasefinish");
		expandBtn.visible = false
	}
	function animationDecreaseFinished(){
		console.log("Decreasefinish");
		expandBtn.visible = true
	}


	function animationTextaeraFinished()
    {
		console.log("animationTextaeraFinished")
		
		text1.y = 0;
		text1.text = text2.text;		
		text2.y = text1.y + text1.height + textArea.vSpace;
		text2.text = text3.text;
		text3.y = text2.y + text2.height + textArea.vSpace;
		text3.text = text4.text;
		text4.y = text3.y + text3.height + textArea.vSpace;
		text4.text = "";
		textArea.height = text3.y + text3.height + textArea.vSpace
	}

	Button {
		id: expandBtn
		x: root.x - 30
		y: 5
		z: 3
		imgWidth : 25
		imgHeight: 26
		pressImg: "qrc:/expand.png"
		normalImg: "qrc:/expand.png"
		sourceImg: "qrc:/expand.png"
		visible: false
		onButtonClicked: expandBtnClicked()
	}

	Rectangle {
		id: root
		width: 270; height: 380			
		color: "#00000000"

		//property string animationType : 'width';
		property int duration : 500
		property int easingType : Easing.OutSine

		property int innerX;
		property int innerY;
		property int innerWidth: width
		property int innerHeight: 380
		property double innerOpacity;



		BorderImage {
			width: root.width; height: root.height
			border { left: 20; top: 65; right: 20; bottom: 20 }
			horizontalTileMode: BorderImage.Stretch
			verticalTileMode: BorderImage.Stretch
			source: "qrc:/ccv.png"
		}
	
	
		Rectangle { // 180
			id: tab
			color: "#00000000"
			width: 180; height: 40
			x: root.x + 20
			y: 8
			Button {
				id: tBtn
				x: tab.x + 5
				y:3
				z: 3
				imgWidth : 32
				imgHeight: 32
				pressImg: "qrc:/tp.png"
				normalImg: "qrc:/t.png"
				sourceImg: "qrc:/tp.png"
				onButtonClicked: onTopBtnClicked(0)
				
			}

			Button {
				id: eBtn
				x: tBtn.x + tBtn.imgWidth + 10
				y:3
				z: 3
				imgWidth : 32
				imgHeight: 32
				pressImg: "qrc:/ep.png"
				normalImg: "qrc:/ef.png"
				sourceImg: "qrc:/ef.png"
				onButtonClicked: onTopBtnClicked(1)
			}

			Button {
				id: sBtn
				x:  eBtn.x + eBtn.imgWidth + 10
				y:3
				z: 3
				imgWidth : 32
				imgHeight: 32
				pressImg: "qrc:/sp.png"
				normalImg: "qrc:/s.png"
				sourceImg: "qrc:/s.png"
				onButtonClicked: onTopBtnClicked(2)
			}

			Button {
				id: collesBtn
				x: root.width - 65
				y: 5
				z: 3
				imgWidth : 25
				imgHeight: 26
				pressImg: "qrc:/colles.png"
				normalImg: "qrc:/colles.png"
				sourceImg: "qrc:/colles.png"
				onButtonClicked: collesBtnClicked()
			}			
		}

		MouseArea{
			onPressed:{
				mouse.accepted = true
			}
		}

		PropertyAnimation {
			id: animWidthIncrease
			target: root
			duration: root.duration
			easing.type: root.easingType
			property: 'x';
			from: root.innerWidth;
			to: 0
			onStopped: animationIncreaseFinished()
		}
		PropertyAnimation {
			id: animWidthDecrease
			target: root
			duration: root.duration
			easing.type: root.easingType
			property: 'x';
			from: 0;
			to: root.innerWidth
			onStopped: animationDecreaseFinished()
		}		

		Rectangle {
			id: textArea
			width: parent.width - 60; 
			height: parent.height - tab.height - 50
			x: 30
			y: tab.y + tab.height + 20
			//color: "green"
			color: "#00000000"
			clip: true
			property int vSpace: 20;
			Text {
				id: text1
				x: 0
				y: 0
				width: parent.width
				//height: parent.height
				clip: true
				font.pointSize: 13
				font.family: "Helvetica"
				color: "#df3a29"
				linkColor: "#b58e24"
				//font.underline: false
				font.weight: Font.Black
				wrapMode: Text.WordWrap
				lineHeight: 1.3
				text: "<li>ssss Text根据需要的空间来设置它。除非设置了wrapMode，否则总是优先宽度而不是高度  <a href=\"http://www.baidu.com\">百度</a></li><li>bbbb <a href=\"http://www.sohu.com\">搜狐</a></li>" //"see the sohu.com adgadgfdg<a href=\"http://www.sohu.com\">图片信息</a>"
				onLinkActivated: Qt.openUrlExternally(link)
			}

			Text {
				id: text2
				x: 0
				y: text1.y + text1.height + textArea.vSpace
				width: parent.width
				//height: parent.height
				clip: true
				font.pointSize: 13
				font.family: "Helvetica"
				color: "#df3a29"
				linkColor: "#b58e24"
				//font.underline: false
				font.weight: Font.Black
				wrapMode: Text.WordWrap
				lineHeight: 1.3
				text: "<li>2015反腐五大猜想:或再有副国级老虎被查  <a href=\"http://news.sohu.com/20150109/n407655211.shtml\">链接地址</a></li>"
				onLinkActivated: Qt.openUrlExternally(link)
			}

			Text {
				id: text3
				x: 0
				y: text2.y + text2.height  + textArea.vSpace
				width: parent.width
				//height: parent.height
				clip: true
				font.pointSize: 13
				font.family: "Helvetica"
				color: "#df3a29"
				linkColor: "#b58e24"
				//font.underline: false
				font.weight: Font.Black
				wrapMode: Text.WordWrap
				lineHeight: 1.3
				text: "<li>哈登3分暴扣逼停尼克斯  <a href=\"http://sports.sohu.com/20150109/n407662352.shtml\">链接地址</a></li>"
				onLinkActivated: Qt.openUrlExternally(link)
			}

			Text {
				id: text4
				x: 0
				y: text3.y + text3.height + textArea.vSpace
				width: parent.width
				//height: parent.height
				clip: true
				font.pointSize: 13
				font.family: "Helvetica"
				color: "#df3a29"
				linkColor: "#b58e24"
				//font.underline: false
				font.weight: Font.Black
				wrapMode: Text.WordWrap
				lineHeight: 1.3
				//text: "111"
				onLinkActivated: Qt.openUrlExternally(link)
			}

			 ParallelAnimation {
				id: animationText
				running: false
				PropertyAnimation {			
					target: text1
					duration: 1500				
					easing.type: Easing.InCirc
					property: 'y';
					from: 0;
					to: -text1.height - textArea.vSpace
				}
				PropertyAnimation {
					target: text2
					duration: 1500				
					easing.type: Easing.InCirc
					property: 'y';
					from: text2.y;
					to: 0
				}
				PropertyAnimation {			
					target: text3
					duration: 1500				
					easing.type: Easing.InCirc
					property: 'y';
					from: text3.y;
					to: text2.height + textArea.vSpace
				}
				PropertyAnimation {			
					target: text4
					duration: 1500				
					easing.type: Easing.InCirc
					property: 'y';
					from: text4.y;
					to: text2.height + textArea.vSpace + text3.height + textArea.vSpace;
				}
				onStopped: animationTextaeraFinished()
			}
		}
    }
}