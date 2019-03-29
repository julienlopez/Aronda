#include "playersstatewidget.hpp"

#include "game.hpp"

#include <numeric_range.hpp>

#include <gsl/gsl_assert>

#include <QHBoxLayout>
#include <QPainter>

namespace Aronda
{

namespace Impl
{
    class PlayerSquare : public QWidget
    {
    public:
        using OptionalSize = boost::optional<std::size_t>;

        explicit PlayerSquare(const Player player, QWidget* parent = nullptr)
            : QWidget(parent)
            , m_player(player)
        {
        }

        virtual ~PlayerSquare() = default;

        void updateDisplay(const OptionalSize display)
        {
            m_display = display;
            update();
        }

    protected:
        virtual void paintEvent(QPaintEvent* evt) override
        {
            Q_UNUSED(evt);
            QPainter p(this);
            p.setRenderHint(QPainter::Antialiasing);
            const auto primary_color = m_player == Aronda::black ? Qt::white : Qt::black;
            const auto background_color = m_player == Aronda::white ? Qt::white : Qt::black;
            if(m_display)
            {
                auto new_pen = p.pen();
                new_pen.setColor(primary_color);
                new_pen.setWidth(10);
                p.setPen(new_pen);
            }
            else
                p.setPen(Qt::NoPen);

            p.setBrush(background_color);
            p.drawRect(rect());

            if(m_display)
            {
                p.setPen(Qt::NoPen);
                p.setBrush(primary_color);
                paintDisplay(p);
            }
        }

    private:
        const Player m_player;
        OptionalSize m_display = boost::none;

        /**
         * @pre m_display.is_initialized()
         */
        void paintDisplay(QPainter& p) const
        {
            Expects(m_display.is_initialized());
            const auto radius = height() / 4;
            for(const auto i : range(*m_display))
            {
                const auto x = (i + 1) * width() / (*m_display + 1) - radius / 2;
                const auto y = height() / 2 - radius / 2;
                p.drawEllipse(x, y, radius, radius);
            }
        }
    };

} // namespace Impl

PlayersStateWidget::PlayersStateWidget(const Game& game, QWidget* parent)
    : QWidget(parent)
    , m_game(game)
{
    auto* hl = new QHBoxLayout;
    for(const auto p : {Aronda::black, Aronda::white})
    {
        auto* square = new Impl::PlayerSquare(p);
        m_squares[p] = square;
        hl->addWidget(square);
    }
    setLayout(hl);
}

void PlayersStateWidget::updateCurrentPlayer()
{
    for(const auto& p : m_squares)
    {
        p.second->updateDisplay(p.first == m_game.currentPlayer() ? boost::make_optional(m_game.stonesLeftToPlay())
                                                                  : boost::none);
    }
}

} // namespace Aronda
