

var LibraryGameGeneral  = {
    $gameGeneral: {
        ctx: null,
        images: [],
        cached_urls: [],
        current_fill_color: '#00000000',
        current_stroke_color: '#00000000',
        current_font: '',
        current_font_size: '10px',
        fonts: [],
        clamp: function(n, min, max) {
            /**/ if (n > max) return max;
            else if (n < min) return min;
            return n;
        },
        numToColor: function(num) {
            num = gameGeneral.clamp(num, 0, 255);
            let str = num.toString(16);
            if (str.length < 2) str = '0' + str;
            return str;
        }
    },
    loadSpriteSheet: function(ascii_url) {
        let url = AsciiToString(ascii_url);

        let is_loaded = 0;
        let width     = 0;
        let height    = 0;
        let id = gameGeneral.images.length;
        let result = _malloc(16);
        setValue(result + 4 * 0, is_loaded, 'i32');
        setValue(result + 4 * 1, id,        'i32');
        setValue(result + 4 * 2, width,     'i32');
        setValue(result + 4 * 3, height,    'i32');

        let image = new Image();
        image.onload = function() {
            /*is_loaded: */ setValue(result + 4 * 0, true,         'i32');
            /*width: */     setValue(result + 4 * 2, image.width,  'i32');
            /*height: */    setValue(result + 4 * 3, image.height, 'i32');
        }
        image.src = url;
        let internal_image = {image: image, pointer: result};
        gameGeneral.images.push(internal_image);

        return result;
    },
    loadFont: function(cstr_family, cstr_url) {
        let family = AsciiToString(cstr_family);
        let url    = AsciiToString(cstr_url);

        let font = new FontFace(family, `url(${url})`);
        font.loaded.then(
            function(f) {
                document.fonts.add(f);
            }, 
            (err) => {
                console.error(err)
            }
        );
        gameGeneral.fonts.push(font);
        font.load();
    },
    background: function(r, g, b, a) {
        let red   = gameGeneral.numToColor(r);
        let green = gameGeneral.numToColor(g);
        let blue  = gameGeneral.numToColor(b);
        let alpha = gameGeneral.numToColor(a);

        if (!gameGeneral.ctx) {
            gameGeneral.ctx = Module['ctx'];
        }
        let ctx = gameGeneral.ctx; 

        let str = `#${red}${green}${blue}${alpha}`
        ctx.fillStyle = str;
        ctx.fillRect(0, 0, canvas.width, canvas.height); 
    },
    drawSprite: function(sprite, screen_x, screen_y, scale_x, scale_y) {
        if (!gameGeneral.ctx) {
            gameGeneral.ctx = Module['ctx'];
        }
        let ctx = gameGeneral.ctx; 

        let id     = getValue(sprite + 4 * 0, 'i32');
        let x      = getValue(sprite + 4 * 1, 'i32');
        let y      = getValue(sprite + 4 * 2, 'i32');
        let width  = getValue(sprite + 4 * 3, 'i32');
        let height = getValue(sprite + 4 * 4, 'i32');

        let screen_width  = width  * scale_x;
        let screen_height = height * scale_y;

        let internal = gameGeneral.images[id];

        ctx.fillStyle = 0;
        ctx.drawImage(internal.image, x, y, width, height, 
            screen_x, screen_y, screen_width, screen_height);
    },
    drawImage: function(url, screen_x, screen_y, width, height) {
        if (!gameGeneral.ctx) {
            gameGeneral.ctx = Module['ctx'];
        }
        let ctx = gameGeneral.ctx; 
        if (gameGeneral.cached_urls[url]) {
            let cached_image = gameGeneral.cached_urls[url];
            if (!cached_image.is_loaded) return;
            let image = cached_image.image;
        
            let screen_width  = width;
            let screen_height = height;

            ctx.fillStyle = 0;
            ctx.drawImage(image, 0, 0, image.height, image.height, 
                screen_x, screen_y, screen_width, screen_height);
        } else {
            let image = new Image();
            image.onload = function() {
                gameGeneral.cached_urls[url].is_loaded = true;
            }
            image.src = AsciiToString(url);
            gameGeneral.cached_urls[url] = {image: image, is_loaded: false};
        }
    },
    fill: function(r, g, b, a) {
        let red   = gameGeneral.numToColor(r);
        let green = gameGeneral.numToColor(g);
        let blue  = gameGeneral.numToColor(b);
        let alpha = gameGeneral.numToColor(a);
        let str = `#${red}${green}${blue}${alpha}`
        gameGeneral.current_fill_color = str;
    },
    stroke: function(r, g, b, a) {
        let red   = gameGeneral.numToColor(r);
        let green = gameGeneral.numToColor(g);
        let blue  = gameGeneral.numToColor(b);
        let alpha = gameGeneral.numToColor(a);
        let str = `#${red}${green}${blue}${alpha}`
        gameGeneral.current_stroke_color = str;
    },
    rect: function(x, y, width, height) {
        if (!gameGeneral.ctx) {
            gameGeneral.ctx = Module['ctx'];
        }
        let ctx = gameGeneral.ctx; 
        ctx.fillStyle = gameGeneral.current_fill_color;
        ctx.fillRect(x, y, width, height);
    },
    ellipse: function(x, y, radius_x, radius_y) {
        if (!gameGeneral.ctx) {
            gameGeneral.ctx = Module['ctx'];
        }
        let ctx = gameGeneral.ctx; 
        ctx.fillStyle = gameGeneral.current_fill_color;
        ctx.beginPath();
        ctx.ellipse(x, y, radius_x, radius_y, 0, 0, 2*Math.PI);
        ctx.fill();
    },
    textAlign: function(align, baseline) {
        if (!gameGeneral.ctx) {
            gameGeneral.ctx = Module['ctx'];
        }
        let ctx = gameGeneral.ctx; 


        switch(baseline) {
        case 0: ctx.textbaseline = 'top';
        case 1: ctx.textbaseline = 'middle';
        case 2: ctx.textbaseline = 'bottom';
        case 3: ctx.textbaseline = 'alphabetic';
        }

        switch(align) {
        case 0: ctx.textAlign = 'left';
        case 1: ctx.textAlign = 'right';
        case 2: ctx.textAlign = 'center';
        }
    },
    setFont: function(px, cstr_font) {
        let font = AsciiToString(cstr_font);
        gameGeneral.current_font = font;
        gameGeneral.current_font_size = `${px}px`;
    },
    text: function(cstr_text, x, y) {
        if (!gameGeneral.ctx) {
            gameGeneral.ctx = Module['ctx'];
        }
        let ctx = gameGeneral.ctx; 
        let text = AsciiToString(cstr_text);

        if (gameGeneral.font != '') {
            ctx.font = `${gameGeneral.current_font_size} ${gameGeneral.current_font}`;
        }
        ctx.fillStyle = gameGeneral.current_fill_color;
        ctx.strokeStyle = gameGeneral.current_stroke_color;
        ctx.fillText(text, x, y);
    }
}

// autoAddDeps(LibrarypWindow, '$Browser')
autoAddDeps(LibrarypWindow, '$gameGeneral')
mergeInto(LibraryManager.library, LibraryGameGeneral);


