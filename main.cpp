#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

void loadStrings( std::string fileName, std::string strings[], int len )
{
    std::fstream file;
    file.open( fileName.c_str() );
    if( file.good() )
    {
        for( int i = 0; i < len; i++ )
        {
            getline( file, strings[i], ';' );
        }
    }
}

bool wasDrawn( int number, int arr[], int howMany )
{
    if( howMany <= 0 )
        return false;
    for( int i = 0; i < howMany; i++ )
    {
        if( arr[i] == number )
            return true;
    }
}

int main( int argc, char *argv[] )
{
    srand( time( NULL ) );
    sf::RenderWindow window( sf::VideoMode(500, 500), "Bingo Generator" );
    sf::Image screen;

    int len = 30;
    std::string strings[len];
    loadStrings( "smieszne.txt", strings, len );
    
    bool wasDrawn[len] = { false };
    int whichLine[len];
    int number;
    
    for( int i = 0; i < len; i++ )
    {
        do
        {
            number = std::rand() % len;
            whichLine[i] = number;
        } while( wasDrawn[number] == true );
        wasDrawn[number] = true;
    }

    while( window.isOpen() )
    {
        sf::Event event;
        while( window.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                window.close();
        }
        window.clear( sf::Color::White );
        
        //draw lines
        sf::VertexArray lines( sf::LineStrip, 2 );
        lines[0].color = sf::Color::Black;
        lines[1].color = sf::Color::Black;
        
        for( int i = 1; i < 5; i++ )
        {
            lines[0].position = sf::Vector2f(i*100, 0);
            lines[1].position = sf::Vector2f(i*100, 500);

            window.draw( lines );
        }   
        for( int i = 1; i < 5; i++ )
        {
            lines[0].position = sf::Vector2f(0, i*100);
            lines[1].position = sf::Vector2f(500, i*100);

            window.draw( lines );
        }   

        //draw text
        sf::Font font;
        if( !font.loadFromFile( "LiberationSans.ttf" ) )
        {
            //sorry
        }

        sf::Text text;
        text.setFont( font );
        text.setCharacterSize( 12 );
        text.setFillColor( sf::Color::Black );
        
        int y = 0;
        int z = 0;
        for( int i = 0; i < 29; i++, z++ )
        {
            if( i != 14 )
            {
                text.setString( strings[ whichLine[i] ].c_str() );
            }else
            {
                text.setString( "       BONUS" );
            }
            text.setPosition( z*100, y*100 );

            if( z % 5 == 0 && z != 0 )
            {
                z = -1;
                y++;
            }
            
            window.draw( text );
        }
        window.display();
        screen = window.capture();
    }
    
    screen.flipVertically();
    screen.saveToFile( "3es22t.png" ); 

    return 0;
}
