
const char* webpage = R"=====(
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Light Dimmer Control</title>

    <style>
    
        body {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
            font-family: Arial, sans-serif;
        }

    .slidecontainer {
        width: 300px;
        justify-content: center;
        margin: 15px;
    }

    .slider {
        -webkit-appearance: none;
        width: 300px;
        height: 50px;
        background: #d3d3d3;
        outline: none;
        opacity: 0.7;
        -webkit-transition: .2s;
        transition: opacity .2s;
    }
    .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 50px;
        height: 50px;
        background: #04AA6D;
        cursor: pointer;
    }

    .slider::-moz-range-thumb {
        width: 50px;
        height: 50px;
        background: #04AA6D;
        cursor: pointer;
    }

.slider:hover {
  opacity: 1;
}

        .buttonON {
            background-color: #04AA6D;
            border: none;
            color: white;
            margin: 10px;
            padding: 10px 20px;
            text-align: center;
            font-size: 24px;
            height:100px;
            width:300px;
        }
        .buttonOFF {
            background-color: #f44336;
            border: none;
            color: white;
            margin: 10px;
            padding: 10px 20px;
            text-align: center;
            font-size: 24px;
            height:100px;
            width:300px;
}

        .button {
            margin: 10px;
            padding: 10px 20px;
            font-size: 24px;
            height:70px;
            width:300px;
        }

    </style>
</head>
<body>

    <h1>Light Dimmer Control</h1>

    <h2>Embedded Systems, FEUP, 2023</h2>

    <div>
    <img src="data:image/png;base64,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"/>
    </div>
    
    <div class="row">
        <div class="column">Pedro Cruz, Mariana Dias, Martinho Figueiredo</div>
    </div>
    </div>

        <div class="row">
        <div class="column">Light Brightness</div>

    </div>
    </div>

    <script>
        function updateSlider(value) {
        fetch(`/slider?value=${value}`);
        }
    </script>

    <div class="slidecontainer">
        <input type="range" min="0" max="100" value="50" class="slider" id="myRange" onchange="updateSlider(this.value)">
    </div>

    <a href="/button1">
        <button class="buttonON button1">ON</button>
    </a>

    <a href="/button2">
        <button class="buttonOFF button2">OFF</button>
    </a>

    <a href="/button3">
        <button class="button button3">OFF 2 sec</button>
    </a>

    <a href="/button4">
        <button class="button button4">OFF 5 sec </button>
    </a>

    <a href="/button5">
        <button class="button button5">OFF 10 sec</button>
    </a>

)=====";