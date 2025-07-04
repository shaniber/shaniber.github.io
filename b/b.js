// b.js? 
//start editing here
let config={
    computeDate:(today)=>{   //specify whatever code you want to spit out the date. Today is a Date object that you should compute against
        const days = ['Sunday','Monday','Tuesday','Wednesday','Thursday','Friday','Saturday'];
        const months = ['January','February','March','April','May','June','July','August','September','October','November','December'];
        return days[today.getDay()]+" "+months[today.getMonth()]+" "+today.getDate()+", "+today.getFullYear()
    },
    greetings: { //specify whatever greetings you want based on the time of day
        morning:"Good morning!",
        afternoon:"Good afternoon!",
        evening:"Good evening!",
        night:"Good night!"
    },
    apps:[  //just keep adding apps in here
        {
            name: 'Hacker news',
            subText:'news.ycombinator.com',
            url: 'https://news.ycombinator.com',
            icon:'/i/images/hacker-news-logo.png'
        },
        {
            name: 'Reddit',
            subText:'reddit.com',
            url: 'https://old.reddit.com',
            icon:'/i/images/reddit-logo.png'
        }
    ],
    categories:[//keep adding categories with links in here
        {
            name:"Auctions",
            links:[
                {   name:"Bodnarus Auctioneering",
                    url:"https://www.bodnarusauctioneering.ca/"
                },
                {
                    name:"PBR Auctions",
                    url:"https://pbrauctions.com/auctions/"
                },
                {
                    name:"McDougall Auctions",
                    url:"https://www.mcdougallbay.com/"
                },
                {
                    name:"Sask Surplus",
                    url:"https://www.sasksurplus.ca/"
                },
                {
                    name:"GC Surplus",
                    url:"https://www.gcsurplus.ca/mn-eng.cfm?snc=wfsav&vndsld=0"
                },
                {
                    name:"SGI Auto Auctions",
                    url:"https://ca.iaai.com/Search/Search/?keyword=SGI"
                }
            ]
        },
        {
            name:"Magic the Gathering Stores",
            links: [
                {
                    name:"Fusion Gaming (Winnipeg)",
                    url:"https://www.fusiongamingonline.com"
                },
                {
                    name:"Face to Face Games (Toronto/Montreal)",
                    url:"https://www.facetofacegames.com/"
                },
                {
                    name:"Rain City Games (Vancouver)",
                    url:"https://www.raincity.games/"
                }
            ]
        },
        {
            name:"epub References",
            links: [
                {   
                    name:"The Softcover Book",
                    url:"https://manual.softcover.io/book/frontmatter"
                },
                {
                    name:"LaTeX for Tabletop",
                    url:"https://vladar.bearblog.dev/latex-for-tabletop/"
                }
            ]
        },
        {
            name:"Game Dev",
            links: [
                {
                    name:"Defold Game Engine",
                    url:"https://defold.com/"
                },
                {
                    name:"CPSS, A Capcom CPS-1 SDK",
                    url:"https://fabiensanglard.net/ccps/"
                },
                {
                    name:"The Book of CP-System",
                    url:"https://github.com/fabiensanglard/cpsb"
                }
            ]
        }

        /*
        {
            name:"Coding",
            links:[
                {
                    name:"Vue.js Docs",
                    url:"https://v3.vuejs.org/api/"
                },
                {
                    name:"MDN JS Docs",
                    url:"https://developer.mozilla.org/en-US/docs/Web/JavaScript"
                },
            ]
        },
        */
    ]
}
//stop editing here
